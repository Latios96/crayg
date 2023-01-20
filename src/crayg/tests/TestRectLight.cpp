#include <catch2/catch.hpp>
#include <scene/Scene.h>
#include "scene/lights/RectLight.h"

namespace crayg {

struct AreaLightFixture {

    AreaLightFixture() {
        areaLight = std::make_shared<RectLight>();
        position = {0, 2, 2};
        areaLight->setPosition(position);
        areaLight->setWidth(1);
        areaLight->setHeight(1);
        areaLight->setIntensity(1);
    }

    std::shared_ptr<RectLight> areaLight;
    Vector3f position;
};

TEST_CASE("RectLight::sampleLightShape") {

    AreaLightFixture areaLightFixture;

    SECTION("sampleLightShape should respect width and height") {
        const float realWidth = 1;
        const float realHeight = 1;

        for (int i = 0; i < 1000; i++) {
            const Vector3f samplePoint = areaLightFixture.areaLight->sampleLightShape();
            REQUIRE(samplePoint.x < (areaLightFixture.position.x + realWidth / 2));
            REQUIRE(samplePoint.x > (areaLightFixture.position.x - realWidth / 2));
            REQUIRE(samplePoint.y < (areaLightFixture.position.y + realHeight / 2));
            REQUIRE(samplePoint.y > (areaLightFixture.position.y - realHeight / 2));
            REQUIRE(samplePoint.z == areaLightFixture.position.z);
        }
    }

    SECTION("sampleLightShape should respect scale") {
        areaLightFixture.areaLight->setWidth(5);
        areaLightFixture.areaLight->setHeight(5);
        const Transform transform =
            Transform(Transform::withPosition(areaLightFixture.position).matrix
                          * Transform::withScale(1.f / 5, 1.f / 5, 1.f / 5).matrix);
        areaLightFixture.areaLight->setTransform(transform);
        const float realWidth = 1;
        const float realHeight = 1;

        for (int i = 0; i < 1000; i++) {
            const Vector3f samplePoint = areaLightFixture.areaLight->sampleLightShape();
            REQUIRE(samplePoint.x < (areaLightFixture.position.x + realWidth / 2));
            REQUIRE(samplePoint.x > (areaLightFixture.position.x - realWidth / 2));
            REQUIRE(samplePoint.y < (areaLightFixture.position.y + realHeight / 2));
            REQUIRE(samplePoint.y > (areaLightFixture.position.y - realHeight / 2));
            REQUIRE(samplePoint.z == areaLightFixture.position.z);
        }
    }
}

TEST_CASE("RectLight::area") {

    AreaLightFixture areaLightFixture;

    SECTION("area should respect width and height") {
        areaLightFixture.areaLight->setWidth(5);
        areaLightFixture.areaLight->setHeight(5);

        const float area = areaLightFixture.areaLight->area();

        REQUIRE(area == Catch::Detail::Approx(25));
    }

    SECTION("area should respect scale") {
        areaLightFixture.areaLight->setWidth(1);
        areaLightFixture.areaLight->setHeight(1);
        const Transform transform =
            Transform(Transform::withPosition(areaLightFixture.position).matrix
                          * Transform::withScale(5, 5, 5).matrix);
        areaLightFixture.areaLight->setTransform(transform);

        const float area = areaLightFixture.areaLight->area();

        REQUIRE(area == Catch::Detail::Approx(25));
    }
}

}

