#include "crayg/scene/Scene.h"
#include "crayg/scene/primitives/Sphere.h"
#include "crayg/scene/shadingnetworks/materials/UsdPreviewSurface.h"
#include <catch2/catch.hpp>

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