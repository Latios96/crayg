#include "scene/lights/AreaLight.h"
#include <catch2/catch.hpp>
#include <scene/Scene.h>

namespace crayg {

TEST_CASE("AreaLight::radiance") {

    class DummyAreaLight : public AreaLight {
      public:
        Vector3f sampleLightShape() const override {
            return transform.toPosition();
        }

        Vector3f getNormal(Vector3f point) override {
            return transform.applyForNormal({0, 0, 1});
        }

        float area() const override {
            return 4;
        }
    };

    DummyAreaLight dummyAreaLight;
    dummyAreaLight.setPosition({0, 2, 2});
    dummyAreaLight.setIntensity(10);

    SECTION("should illuminate point in front of the areaLight") {
        const Vector3f point(0, 2, 4);
        const Vector3f normal(0, 0, -1);

        auto radiance = dummyAreaLight.radiance(point, normal);

        REQUIRE(radiance == Light::Radiance(Color::createGrey(3.1830988f), Ray({0, 2, 4}, {0, 0, -2})));
    }

    SECTION("should not illuminate point in back of the areaLight") {
        Vector3f point(0, 2, 1);
        const Vector3f normal(0, 0, -1);

        auto radiance = dummyAreaLight.radiance(point, normal);

        REQUIRE(radiance == Light::Radiance(Color::createBlack(), Ray({0, 2, 1}, {0, 0, 1})));
    }

    SECTION(
        "should not illuminate point in back of the areaLight, also if surface normal is in same direction as light") {
        Vector3f point(0, 2, -1);
        const Vector3f normal(0, 0, 11);

        auto radiance = dummyAreaLight.radiance(point, normal);

        REQUIRE(radiance.radiance < Color::createBlack());
    }
}

}
