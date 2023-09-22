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

LensRayLookupTable::LensRayLookupTable(const Resolution &resolution, int samplesPerPixel, bool useSpectralLensing)
    : resolution(resolution), samplesPerPixel(samplesPerPixel), useSpectralLensing(useSpectralLensing) {
}

void LensRayLookupTable::generate(CameraModel &cameraModel) {
    const int spectralFactor = useSpectralLensing ? 3 : 1;
    unsigned long long elementsCount =
        resolution.getWidth() * resolution.getHeight() * samplesPerPixel * spectralFactor;
    Logger::info("Allocating {:L} GB for Ray-LUT", (elementsCount * sizeof(Ray)) * 1e-9);
    Logger::info("Elements count: {:L}", elementsCount);
    Logger::info("Max vector size: {:L}", rays.max_size());
    rays.resize(elementsCount);
    Logger::info("Vector capacity: {:L}", rays.capacity());

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
}

void LensRayLookupTable::sampleImageBucket(CameraModel &cameraModel, ImageBucket &imageBucket) {
    for (auto pixel : ImageIterators::lineByLine(imageBucket)) {
        const auto pixelPos = pixel + imageBucket.getPosition();
        for (int i = 0; i < samplesPerPixel; i++) {
            const Vector2f samplePos = Random::randomVector2f() + pixelPos;
            if (useSpectralLensing) {
                const auto ray_r = cameraModel.createPrimaryRay(samplePos.x, samplePos.y, WavelengthsRgb::R).ray;
                storeRay(ray_r, pixelPos, i, 0);
                const auto ray_g = cameraModel.createPrimaryRay(samplePos.x, samplePos.y, WavelengthsRgb::G).ray;
                storeRay(ray_g, pixelPos, i, 1);
                const auto ray_b = cameraModel.createPrimaryRay(samplePos.x, samplePos.y, WavelengthsRgb::B).ray;
                storeRay(ray_b, pixelPos, i, 2);
            } else {
                const auto ray =
                    cameraModel.createPrimaryRay(samplePos.x, samplePos.y, FraunhoferLines::SODIUM.wavelength).ray;
                storeRay(ray, pixelPos, i, 0);
            }
        }
    }
}

Ray LensRayLookupTable::getRay(const Vector2i &pixel, int sampleNumber, int wavelengthIndex) {
    auto rayNumber = getVec3fIndex(pixel, sampleNumber, wavelengthIndex);
    return rays[rayNumber]; // todo respect camera transforms in the future
}

int LensRayLookupTable::getVec3fIndex(const Vector2i &pixel, int sampleNumber, int offsetInRay) {
    const int spectralFactor = useSpectralLensing ? 3 : 1;
    return ((pixel.x + pixel.y * resolution.getWidth()) * samplesPerPixel + sampleNumber) * spectralFactor +
           offsetInRay;
}

void LensRayLookupTable::storeRay(const std::optional<Ray> &ray, const Vector2i &pixelPos, int sampleNumber,
                                  int waveLengthIndex) {
    const int pixelIndex = getVec3fIndex(pixelPos, sampleNumber, waveLengthIndex);
    if (ray) {
        rays[pixelIndex] = *ray;
    } else {
        rays[pixelIndex] = Ray();
    }
}
} // crayg