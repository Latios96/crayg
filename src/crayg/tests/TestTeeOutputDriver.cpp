#include <catch2/catch.hpp>
#include <fakeit.hpp>
#include <outputdrivers/OutputDriver.h>
#include <outputdrivers/TeeOutputDriver.h>

namespace crayg {

TEST_CASE("TeeOutputDriver should forward methods") {
    fakeit::Mock<OutputDriver> mockLeft;
    fakeit::When(Method(mockLeft, initialize)).AlwaysReturn();
    fakeit::When(Method(mockLeft, prepareTile)).AlwaysReturn();
    fakeit::When(Method(mockLeft, writeTileImageBuffer)).AlwaysReturn();
    fakeit::When(Method(mockLeft, writeImageMetadata)).AlwaysReturn();
    fakeit::Mock<OutputDriver> mockRight;
    fakeit::When(Method(mockRight, initialize)).AlwaysReturn();
    fakeit::When(Method(mockRight, prepareTile)).AlwaysReturn();
    fakeit::When(Method(mockRight, writeTileImageBuffer)).AlwaysReturn();
    fakeit::When(Method(mockRight, writeImageMetadata)).AlwaysReturn();
    TeeOutputDriver teeOutputDriver(mockLeft.get(), mockRight.get());

    SECTION("should forward initialize") {
        teeOutputDriver.initialize(ImageSpec());

        fakeit::Verify(Method(mockLeft, initialize)).Once();
        fakeit::Verify(Method(mockRight, initialize)).Once();
    }

    SECTION("should forward prepareTile") {
        teeOutputDriver.prepareTile(ImageTile());

        fakeit::Verify(Method(mockLeft, prepareTile)).Once();
        fakeit::Verify(Method(mockRight, prepareTile)).Once();
    }

    SECTION("should forward writeTileImageBuffer") {
        teeOutputDriver.writeTileImageBuffer(TileImageBuffer({0, 0}, 10, 10));

        fakeit::Verify(Method(mockLeft, writeTileImageBuffer)).Once();
        fakeit::Verify(Method(mockRight, writeTileImageBuffer)).Once();
    }

    SECTION("should forward writeImageMetadata") {
        teeOutputDriver.writeImageMetadata(ImageMetadata());

        fakeit::Verify(Method(mockLeft, writeImageMetadata)).Once();
        fakeit::Verify(Method(mockRight, writeImageMetadata)).Once();
    }
}

}
