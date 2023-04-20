#include "LensRayLookupTable.h"
#include "image/ImageBucket.h"
#include "image/ImageBucketSequences.h"
#include "image/ImageIterators.h"
#include "sampling/Random.h"
#include "utils/ProgressReporter.h"
#include "utils/StopWatch.h"
#include <tbb/parallel_for.h>

namespace crayg {
LensRayLookupTable::LensRayLookupTable(const Resolution &resolution, int samplesPerPixel)
    : resolution(resolution), samplesPerPixel(samplesPerPixel) {
}

int rayIndex(const Vector2i &pixel, int sample, int width) {
    return pixel.x + (width * pixel.y) + sample;
}

void LensRayLookupTable::generate(CameraModel &cameraModel) {
    dirs.resize(resolution.getWidth() * resolution.getHeight() * samplesPerPixel);
    std::vector<ImageBucket> bucketSequence = ImageBucketSequences::lineByLine(resolution, 8);
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
    }*/
}

void LensRayLookupTable::sampleImageBucket(CameraModel &cameraModel, ImageBucket &imageBucket) {
    for (auto pixel : ImageIterators::lineByLine(imageBucket)) {
        const auto pixelPos = pixel + imageBucket.getPosition();
        for (int i = 0; i < samplesPerPixel; i++) {
            const auto ray = cameraModel.createPrimaryRay(pixelPos.x + Random::random(), pixelPos.y + Random::random());
            const int pixelIndex = rayIndex(pixelPos, i, resolution.getWidth());
            if (ray) {
                dirs[pixelIndex] = ray->direction;
            } else {
                dirs[pixelIndex] = Vector3f(0, 0, 0);
            }
        }
    }
}

void LensRayLookupTable::write(const std::string &path) {

    InformativeScopedStopWatch generateRays("Write ray data");
    std::ofstream out;
    out.open(path, std::ios::out | std::ios::binary);
    out.write(reinterpret_cast<const char *>(dirs.data()), sizeof(float) * dirs.size() * 3);
    out.close();
}

void LensRayLookupTable::read(const std::string &path) {

    InformativeScopedStopWatch generateRays("Read ray data");
    dirs.resize(resolution.getWidth() * resolution.getHeight() * 8);
    std::ifstream fin("lensraylookup.dat", std::ios::binary);
    fin.read(reinterpret_cast<char *>(dirs.data()), sizeof(float) * dirs.size() * 3);
}
} // crayg