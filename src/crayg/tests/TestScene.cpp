#include "scene/primitives/Sphere.h"
#include <catch2/catch.hpp>
#include <scene/Scene.h>
#include <scene/materials/UsdPreviewSurface.h>

namespace crayg {

TEST_CASE("addObjectToScene") {
    Scene scene;
    const std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>(Vector3f(0, 0, 0), 1.5f);
    const std::shared_ptr<Material> diffuseMaterial = std::make_shared<UsdPreviewSurface>(Color::createGrey(0.5f));

    SECTION("should add object with no material to scene") {
        scene.addObject(sphere);

        REQUIRE(scene.objects.size() == 1);
    }

    SECTION("should add object with known material to scene") {
        sphere->setMaterial(diffuseMaterial);

        scene.addObject(sphere);

        REQUIRE(scene.objects.size() == 1);
    }
}

}