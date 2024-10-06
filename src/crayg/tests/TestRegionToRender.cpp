#include "scene/RegionToRender.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("RegionToRender::construct") {

    SECTION("should construct pixel region") {
        const RegionToRender pixelRegion(PixelRegion({100, 200}, {300, 400}));

        REQUIRE(pixelRegion.isPixelRegion());
    }

    SECTION("should construct ndc region") {
        const RegionToRender ndcRegion(NDCRegion({{0.1, 0.2}, {0.3, 0.4}}));

        REQUIRE(ndcRegion.isNDCRegion());
    }
}

TEST_CASE("RegionToRender::fromString") {

    SECTION("should parse valid pixel region from string") {
        auto regionToRender = RegionToRender::fromString(" px: [ (100,200), (300, 400)]");

        REQUIRE(regionToRender.isPixelRegion());
        REQUIRE(std::get<PixelRegion>(regionToRender.region) == PixelRegion({{100, 200}, {300, 400}}));
    }

    SECTION("should not parse invalid pixel region from string") {
        REQUIRE_THROWS_AS(RegionToRender::fromString("px:[(1000);(200,200)]"), std::runtime_error);
    }
    SECTION("should parse valid ndc region from string") {
        auto regionToRender = RegionToRender::fromString("ndc:[(0.1,0.2),(0.3,0.4)]");

        REQUIRE(regionToRender.isNDCRegion());
        REQUIRE(std::get<NDCRegion>(regionToRender.region) == NDCRegion({{0.1, 0.2}, {0.3, 0.4}}));
    }

    SECTION("should not parse invalid ndc region from string") {
        REQUIRE_THROWS_AS(RegionToRender::fromString("ndc:[(-100,100),(200,20]"), std::runtime_error);
    }

    SECTION("should not parse invalid format") {
        REQUIRE_THROWS_AS(RegionToRender::fromString("invalid:[(100,100),(200,200)]"), std::runtime_error);
    }
}

TEST_CASE("RegionToRender::toString") {

    SECTION("should serialize pixel region to string") {
        RegionToRender regionToRender(PixelRegion({{100, 200}, {300, 400}}));

        REQUIRE(regionToRender.toString() == "px:[(100,200),(300,400)]");
    }

    SECTION("should serialize ndc region to string") {
        RegionToRender regionToRender(NDCRegion({{0.1, 0.2}, {0.3, 0.4}}));

        REQUIRE(regionToRender.toString() == "ndc:[(0.100,0.200),(0.300,0.400)]");
    }
}

TEST_CASE("RegionToRender::toPixelRegion") {

    SECTION("should return pixel region unmodified") {
        const PixelRegion originalRegion = PixelRegion({{100, 200}, {300, 400}});
        RegionToRender regionToRender(originalRegion);

        REQUIRE(regionToRender.toPixelRegion(Resolution(1920, 1080)) == originalRegion);
    }

    SECTION("should return pixel region from ndc") {
        RegionToRender regionToRender(NDCRegion({{0.1, 0.2}, {0.3, 0.4}}));

        REQUIRE(regionToRender.toPixelRegion(Resolution(1920, 1080)) == PixelRegion{{192, 864}, {576, 648}});
    }
}

TEST_CASE("RegionToRender::toNdcRegion") {

    SECTION("should return pixel region") {
        RegionToRender regionToRender(PixelRegion({{100, 200}, {300, 400}}));

        const NDCRegion ndcRegion = regionToRender.toNDCRegion(Resolution(1920, 1080));
        REQUIRE(ndcRegion.min.x == Catch::Detail::Approx(0.052083332f));
        REQUIRE(ndcRegion.min.y == Catch::Detail::Approx(0.8148148f));
        REQUIRE(ndcRegion.max.x == Catch::Detail::Approx(0.15625f));
        REQUIRE(ndcRegion.max.y == Catch::Detail::Approx(0.6296296f));
    }

    SECTION("should return ndc region unmodified") {
        const NDCRegion originalRegion = NDCRegion({{0.1, 0.2}, {0.3, 0.4}});
        RegionToRender regionToRender(originalRegion);

        REQUIRE(regionToRender.toNDCRegion(Resolution(1920, 1080)) == originalRegion);
    }
}

}