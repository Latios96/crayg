#include "BucketStats.h"
#include "utils/Heatmap.h"
#include <image/ImageAlgorithms.h>

namespace crayg {

void BucketStats::processBucketTime(Film &film, const ImageBucket &imageBucket,
                                    const std::chrono::steady_clock::time_point &startTime) {
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    const auto secondsForBucket =
        std::chrono::duration_cast<std::chrono::milliseconds>(end - startTime).count() / 1000.f;

    for (auto bucketPos : AreaIterators::lineByLine(imageBucket)) {
        const Vector2i pixel = bucketPos + imageBucket.getPosition();
        film.addSample("absoluteRenderTime", pixel, Color::createGrey(secondsForBucket));
    }

    imageBucketTimes.push_back({imageBucket, secondsForBucket});
}

void BucketStats::processBucketTimes(NextGenOutputDriver &outputDriver, const Resolution &resolution) {
    const ImageBucketTime bucketWithMaxTime =
        *std::max_element(imageBucketTimes.begin(), imageBucketTimes.end(),
                          [](ImageBucketTime &a, ImageBucketTime &b) { return a.seconds < b.seconds; });
    const float maxTime = bucketWithMaxTime.seconds;

    auto maybeBuffer = outputDriver.getFilm().getBufferVariantPtrByName("relativeRenderTime");
    if (!maybeBuffer) {
        return;
    }

    auto buffer = FilmBufferVariants::getAsValueBufferVariantPtr(*maybeBuffer);

    for (auto &imageBucketTime : imageBucketTimes) {
        float relativeTime = imageBucketTime.seconds / maxTime;
        relativeTime = std::isnan(relativeTime) ? 0 : relativeTime;
        const Color relativeTimeColor = MagmaHeatmap::lookup(relativeTime);
        for (auto pixel : AreaIterators::lineByLine(imageBucketTime.imageBucket)) {
            const auto globalPos = imageBucketTime.imageBucket.getPosition() + pixel;
            std::visit([&globalPos, &relativeTimeColor](auto buf) { buf->write(globalPos, relativeTimeColor); },
                       *buffer);
        }
    }

    outputDriver.updateChannel("relativeRenderTime");
}
}