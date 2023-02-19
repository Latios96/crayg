#include <catch2/catch.hpp>
#include <fakeit.hpp>
#include <image/OutputDriver.h>
#include <image/TeeOutputDriver.h>

namespace crayg {

TEST_CASE("TeeOutputDriver should forward methods") {
    fakeit::Mock<OutputDriver> mockLeft;
    fakeit::When(Method(mockLeft, initialize)).AlwaysReturn();
    fakeit::When(Method(mockLeft, prepareBucket)).AlwaysReturn();
    fakeit::When(Method(mockLeft, writeBucketImageBuffer)).AlwaysReturn();
    fakeit::When(Method(mockLeft, writeImageMetadata)).AlwaysReturn();
    fakeit::Mock<OutputDriver> mockRight;
    fakeit::When(Method(mockRight, initialize)).AlwaysReturn();
    fakeit::When(Method(mockRight, prepareBucket)).AlwaysReturn();
    fakeit::When(Method(mockRight, writeBucketImageBuffer)).AlwaysReturn();
    fakeit::When(Method(mockRight, writeImageMetadata)).AlwaysReturn();
    TeeOutputDriver teeOutputDriver(mockLeft.get(), mockRight.get());

    SECTION("should forward initialize") {
        teeOutputDriver.initialize(ImageSpec());

        fakeit::Verify(Method(mockLeft, initialize)).Once();
        fakeit::Verify(Method(mockRight, initialize)).Once();
    }

    SECTION("should forward prepareBucket") {
        teeOutputDriver.prepareBucket(ImageBucket());

        fakeit::Verify(Method(mockLeft, prepareBucket)).Once();
        fakeit::Verify(Method(mockRight, prepareBucket)).Once();
    }

    SECTION("should forward writeBucketImageBuffer") {
        teeOutputDriver.writeBucketImageBuffer(BucketImageBuffer(0, 0, 10, 10));

        fakeit::Verify(Method(mockLeft, writeBucketImageBuffer)).Once();
        fakeit::Verify(Method(mockRight, writeBucketImageBuffer)).Once();
    }

    SECTION("should forward writeImageMetadata") {
        teeOutputDriver.writeImageMetadata(ImageMetadata());

        fakeit::Verify(Method(mockLeft, writeImageMetadata)).Once();
        fakeit::Verify(Method(mockRight, writeImageMetadata)).Once();
    }
}

}
