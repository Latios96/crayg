//
// Created by Jan on 15.11.2020.
//

#include <catch2/catch.hpp>
#include <scene/Scene.h>
#include <scene/DiffuseMaterial.h>

TEST_CASE("addObjectToScene") {
    Scene scene;
    const std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>(Vector3f(0, 0, 0), 1.5);
    const std::shared_ptr<Material> diffuseMaterial = std::make_shared<DiffuseMaterial>(Color::createGrey(0.5f));

    SECTION("should add object with no material to scene") {
        scene.addObject(sphere);

        REQUIRE(scene.objects.size() == 1);
    }

    SECTION("should add object with known material to scene") {
        scene.materials.push_back(diffuseMaterial);
        sphere->setMaterial(diffuseMaterial);

        scene.addObject(sphere);

        REQUIRE(scene.objects.size() == 1);
        REQUIRE(scene.materials.size() == 1);
    }

    SECTION("should add object with unknown material to scene") {
        sphere->setMaterial(diffuseMaterial);

        scene.addObject(sphere);

        REQUIRE(scene.objects.size() == 1);
        REQUIRE(scene.materials.size() == 1);
    }

    SECTION("cannot add material without name") {
        const std::shared_ptr<Material> material = std::make_shared<DiffuseMaterial>("", Color::createGrey(0.5f));
        REQUIRE_THROWS_AS(scene.addMaterial(material), std::runtime_error);
    }

    SECTION("material name has to be unique") {
        const std::shared_ptr<Material> material1 = std::make_shared<DiffuseMaterial>("name", Color::createGrey(0.5f));
        const std::shared_ptr<Material> material2 = std::make_shared<DiffuseMaterial>("name", Color::createGrey(0.5f));
        scene.addMaterial(material1);

        REQUIRE_THROWS_AS(scene.addMaterial(material2), std::runtime_error);
    }
}

TEST_CASE("findMaterialByNameInScene") {
    Scene scene;
    const std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>(Vector3f(0, 0, 0), 1.5);
    const std::shared_ptr<Material>
        diffuseMaterial = std::make_shared<DiffuseMaterial>("myMaterial", Color::createGrey(0.5f));
    scene.addMaterial(diffuseMaterial);

    SECTION("should find existing material") {
        REQUIRE(scene.materialByName("myMaterial") == diffuseMaterial);
    }

    SECTION("should not find exisiting material") {
        REQUIRE(scene.materialByName("<sdgf>") == nullptr);
    }
}