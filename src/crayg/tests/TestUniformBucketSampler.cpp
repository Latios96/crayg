#include "renderer/bucketsamplers/UniformBucketSampler.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("UniformBucketSampler::addRequiredImageSpecs") {

    SECTION("should add required image channels") {
        UniformBucketSampler uniformBucketSampler(4, [](Vector2f samplePos) { return Color::createWhite(); });

        BucketImageBuffer bucketImageBuffer(ImageBucket({0, 0}, 5, 5));
        ImageSpecBuilder builder(Resolution::deduce(bucketImageBuffer.imageBucket));
        uniformBucketSampler.addRequiredImageSpecs(builder);
        auto imageSpec = builder.finish();

        REQUIRE(imageSpec.channels == std::vector<ChannelSpec>({{"rgb", PixelFormat::FLOAT, 3}}));
    }
}

TEST_CASE("UniformBucketSampler::sampleBucket") {

    SECTION("should sample bucket uniformly") {
        int renderSampleCount = 0;
        UniformBucketSampler uniformBucketSampler(4, [&renderSampleCount](Vector2f samplePos) {
            renderSampleCount++;
            return Color::createWhite();
        });

        BucketImageBuffer bucketImageBuffer(ImageBucket({0, 0}, 5, 5));
        ImageSpecBuilder builder(Resolution::deduce(bucketImageBuffer.imageBucket));
        uniformBucketSampler.addRequiredImageSpecs(builder);
        bucketImageBuffer.image.addChannelsFromSpec(builder.finish());

        uniformBucketSampler.sampleBucket(bucketImageBuffer);

        REQUIRE(renderSampleCount == 5 * 5 * 4 * 4);
    }
}

}