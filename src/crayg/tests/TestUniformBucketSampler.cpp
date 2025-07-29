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

        REQUIRE(imageSpec.channels == std::vector<ChannelSpec>({{"rgb", PixelFormat::FLOAT32, 3}}));
    }
}

}