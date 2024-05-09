#include "BucketStats.h"
#include <image/ImageAlgorithms.h>

namespace crayg {

void BucketStats::processBucketTime(BucketImageBuffer &bucketImageBuffer,
                                    const std::chrono::steady_clock::time_point &startTime) {
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    const auto secondsForBucket =
        std::chrono::duration_cast<std::chrono::milliseconds>(end - startTime).count() / 1000.f;
    ImageAlgorithms::fill(*bucketImageBuffer.image.getChannel("absoluteRenderTime"),
                          Color::createGrey(secondsForBucket));

    imageBucketTimes.push_back({bucketImageBuffer.imageBucket, secondsForBucket});
}

void BucketStats::processBucketTimes(OutputDriver &outputDriver, const Resolution &resolution) {
    const ImageBucketTime bucketWithMaxTime =
        *std::max_element(imageBucketTimes.begin(), imageBucketTimes.end(),
                          [](ImageBucketTime &a, ImageBucketTime &b) { return a.seconds < b.seconds; });
    const float maxTime = bucketWithMaxTime.seconds;

    auto pixelBuffer = PixelBuffer::createRgbFloat(resolution);
    const auto heatmap = Gradients::heatmap();

    for (auto &imageBucketTime : imageBucketTimes) {
        float relativeTime = imageBucketTime.seconds / maxTime;
        relativeTime = std::isnan(relativeTime) ? 0 : relativeTime;
        const Color relativeTimeColor = heatmap.interpolate(relativeTime);
        ImageAlgorithms::fill(*pixelBuffer, relativeTimeColor, imageBucketTime.imageBucket);
    }

    outputDriver.updateChannel("relativeRenderTime", pixelBuffer.get());
}
} // crayg