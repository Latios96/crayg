#include "sceneIO/write/usd/UsdPathFactory.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("UsdPathFactory::getPathForName") {

    UsdPathFactory usdPathFactory;

    SECTION("should return name if name is not empty and already starts with '/'") {
        const pxr::SdfPath path = usdPathFactory.getPathForName("/sphere", "Sphere");

        REQUIRE(path.GetString() == "/sphere");
    }

    SECTION("should prepend '/' to name if name is not empty") {
        const pxr::SdfPath path = usdPathFactory.getPathForName("sphere", "Sphere");

        REQUIRE(path.GetString() == "/sphere");
    }

    SECTION("should return type and counter for empty name") {
        const pxr::SdfPath path = usdPathFactory.getPathForName("", "Sphere");

        REQUIRE(path.GetString() == "/Sphere0");
    }

    SECTION("should return incremented counter") {
        usdPathFactory.getPathForName("", "Sphere");
        const pxr::SdfPath path = usdPathFactory.getPathForName("", "Sphere");

        REQUIRE(path.GetString() == "/Sphere1");
    }
}

}