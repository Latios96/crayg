#include "crayg/scene/lights/Light.h"
#include "crayg/scene/shadingnetworks/materials/EmissiveMaterial.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("Light::radiance") {

    Light light(Transform::withPosition({0, 5, 0}), 1);

    SECTION("should return correct radiance") {
        const Vector3f point(0, 0, 0);
        const Vector3f normal(0, 1, 0);

        auto radiance = light.radiance(point, normal);

        REQUIRE(radiance.radiance == Color::createGrey(0.19999999f));
        REQUIRE(radiance.ray == Ray({0, 0, 0}, {0, 5, 0}));
    }
}

TEST_CASE("Light::construct") {

    Light light(Transform::withPosition({0, 5, 0}), 1);

    SECTION("should have emissive material") {
        REQUIRE(light.getMaterial());

        REQUIRE(light.getMaterial()->getType() == "EmissiveMaterial");
        auto emissiveMaterial = std::dynamic_pointer_cast<EmissiveMaterial>(light.getMaterial());
        REQUIRE(emissiveMaterial->emission == Color::createWhite());
    }
}

TEST_CASE("Light::setIntensity") {

    Light light(Transform::withPosition({0, 5, 0}), 1);

    SECTION("should change emission on material") {
        light.setIntensity(5);

        auto emissiveMaterial = std::dynamic_pointer_cast<EmissiveMaterial>(light.getMaterial());
        REQUIRE(emissiveMaterial->emission == Color::createGrey(5));
    }
}

TEST_CASE("Light::setColor") {

    Light light(Transform::withPosition({0, 5, 0}), 1);

    SECTION("should change emission on material") {
        light.setColor(Color::createRed());

        auto emissiveMaterial = std::dynamic_pointer_cast<EmissiveMaterial>(light.getMaterial());
        REQUIRE(emissiveMaterial->emission == Color::createRed());
    }
}

}
