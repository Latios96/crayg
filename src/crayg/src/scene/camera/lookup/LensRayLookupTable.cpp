#include "LensRayLookupTable.h"
#include "image/ImageBucket.h"
#include "image/imageiterators/buckets/ImageBucketSequences.h"
#include "image/imageiterators/pixels/ImageIterators.h"
#include "sampling/Random.h"
#include "scene/camera/realistic/Wavelengths.h"
#include "utils/ProgressReporter.h"
#include "utils/StopWatch.h"
#include <tbb/parallel_for.h>

namespace crayg {

LensRayLookupTable::LensRayLookupTable(const Resolution &resolution, int samplesPerPixel)
    : resolution(resolution), samplesPerPixel(samplesPerPixel) {
}

void LensRayLookupTable::generate(CameraModel &cameraModel) {
    dirs.resize(resolution.getWidth() * resolution.getHeight() * samplesPerPixel * 2);
    std::vector<ImageBucket> bucketSequence =
        ImageBucketSequences::getSequence(resolution, 8, BucketSequenceType::LINE_BY_LINE);
    ProgressReporter reporter = ProgressReporter::createLoggingProgressReporter(static_cast<int>(bucketSequence.size()),
                                                                                "Generating lookup table");
    tbb::parallel_for(static_cast<std::size_t>(0), bucketSequence.size(),
                      [this, &reporter, &bucketSequence, &cameraModel](int i) {
                          ImageBucket imageBucket = bucketSequence[i];
                          sampleImageBucket(cameraModel, imageBucket);
                          reporter.iterationDone();
                      });
    /*for (auto bucket : bucketSequence) {
        sampleImageBucket(cameraModel, bucket);
        reporter.iterationDone();
    }*/
}

void LensRayLookupTable::sampleImageBucket(CameraModel &cameraModel, ImageBucket &imageBucket) {
    for (auto pixel : ImageIterators::lineByLine(imageBucket)) {
        const auto pixelPos = pixel + imageBucket.getPosition();
        for (int i = 0; i < samplesPerPixel; i++) {
            const auto ray = cameraModel
                                 .createPrimaryRay(pixelPos.x + Random::random(), pixelPos.y + Random::random(),
                                                   FraunhoferLines::SODIUM.wavelength)
                                 .ray;
            const int pixelIndex = getVec3fIndex(pixelPos, i, 0);
            if (ray) {
                dirs[pixelIndex] = ray->startPoint;
                dirs[pixelIndex + 1] = ray->direction;
            } else {
                dirs[pixelIndex] = Vector3f(0, 0, 0);
                dirs[pixelIndex + 1] = Vector3f(0, 0, 0);
            }
        }
    }
}

void LensRayLookupTable::write(const std::string &path) {

    InformativeScopedStopWatch generateRays("Write ray data");
    std::ofstream out;
    out.open(path, std::ios::out | std::ios::binary);
    out.write(reinterpret_cast<const char *>(dirs.data()), sizeof(float) * dirs.size() * 3 * 2);
    out.close();
}

void LensRayLookupTable::read(const std::string &path) {

    InformativeScopedStopWatch generateRays("Read ray data");
    dirs.resize(resolution.getWidth() * resolution.getHeight() * samplesPerPixel);
    std::ifstream fin(path, std::ios::binary);
    fin.read(reinterpret_cast<char *>(dirs.data()), sizeof(float) * dirs.size() * 3 * 2);
}

Ray LensRayLookupTable::getRay(const Vector2i &pixel, int sampleNumber) {
    auto rayNumber = getVec3fIndex(pixel, sampleNumber, 0);
    return Ray(dirs[rayNumber], dirs[rayNumber + 1]); // todo respect camera transforms in the future
}

int LensRayLookupTable::getVec3fIndex(const Vector2i &pixel, int sampleNumber, int offsetInRay) {
    return (pixel.x + pixel.y * resolution.getWidth()) * samplesPerPixel * 2 + sampleNumber * 2 + offsetInRay;
}
} // crayg