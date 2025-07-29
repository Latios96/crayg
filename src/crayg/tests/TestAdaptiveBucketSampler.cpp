#include "renderer/bucketsamplers/AdaptiveBucketSampler.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("AdaptiveBucketSampler::addRequiredImageSpecs") {

    SECTION("should add required image channels") {
        AdaptiveBucketSampler adaptiveBucketSampler(
            4, [](Vector2f samplePos) { return Color::createWhite(); }, 8, 0.007f);

        BucketImageBuffer bucketImageBuffer(ImageBucket({0, 0}, 5, 5));
        ImageSpecBuilder builder(Resolution::deduce(bucketImageBuffer.imageBucket));
        adaptiveBucketSampler.addRequiredImageSpecs(builder);
        auto imageSpec = builder.finish();

        REQUIRE(imageSpec.channels ==
                std::vector<ChannelSpec>({{"rgb", PixelFormat::FLOAT32, 3}, {"sampleCount", PixelFormat::FLOAT32, 3}}));
    }
}

TEST_CASE("AdaptiveBucketSampler::shouldTerminate") {
    AdaptiveBucketSampler adaptiveBucketSampler(
        4, [](Vector2f samplePos) { return Color::createWhite(); }, 8, 0.007f);

    SECTION("should return false if error is larger than max error and max samples are not reached") {
        auto shouldTerminate = adaptiveBucketSampler.shouldTerminate(2, 0.1f);

        REQUIRE_FALSE(shouldTerminate);
    }

    SECTION("should return true if error is smaller than max error and max samples are not reached") {
        auto shouldTerminate = adaptiveBucketSampler.shouldTerminate(2, 0.001f);

        REQUIRE(shouldTerminate);
    }

    SECTION("should return true if error is larger than max error and max samples are reached") {
        auto shouldTerminate = adaptiveBucketSampler.shouldTerminate(17, 0.1f);

        REQUIRE(shouldTerminate);
    }
}

TEST_CASE("AdaptiveBucketSampler::evaluateErrorMetric") {
    AdaptiveBucketSampler adaptiveBucketSampler(
        4, [](Vector2f samplePos) { return Color::createWhite(); }, 8, 0.007f);

    SECTION("should return 0 if fully sampled color is nan") {
        const float error =
            adaptiveBucketSampler.evaluateErrorMetric(Color::createGrey(std::nan("")), Color::createWhite());

        REQUIRE(error == 0);
    }

    SECTION("should return 0 if half sampled color is nan") {
        const float error =
            adaptiveBucketSampler.evaluateErrorMetric(Color::createWhite(), Color::createGrey(std::nan("")));

        REQUIRE(error == 0);
    }

    SECTION("should return 0 if fullySampled color is black") {
        const float error = adaptiveBucketSampler.evaluateErrorMetric(Color::createBlack(), Color::createWhite());

        REQUIRE(error == 0);
    }

    SECTION("should return the calculated error") {
        const float error = adaptiveBucketSampler.evaluateErrorMetric(Color(0.1f, 0.2f, 0.3f), Color(0.4f, 0.5f, 0.6f));

        REQUIRE(error == Catch::Detail::Approx(1.1619f));
    }
}

}