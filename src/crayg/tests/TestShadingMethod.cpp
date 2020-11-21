//
// Created by Jan Honsbrok on 11.11.18.
//
#include <catch2/catch.hpp>
#include <scene/Scene.h>
#include <ShadingMethod.h>
#include <scene/DiffuseMaterial.h>

TEST_CASE("ShadingMethod") {
    Scene scene;

    std::shared_ptr<Light> light = std::make_shared<Light>(Transform::withPosition(Vector3f(5, 0, 0)), 1);
    scene.addLight(light);

    std::shared_ptr<DiffuseMaterial>
        defaultMaterial = std::make_shared<DiffuseMaterial>("defaultMaterial", Color::createWhite());
    std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>(Vector3f(), 1);
    sphere->setMaterial(defaultMaterial);
    scene.addObject(sphere);

    ShadingMethod lambertMethod(scene);

    SECTION("colorForLightIsAmbientColor") {
        Color shadedColor = lambertMethod.lambertShading(Vector3f(-1, 0, 0), *sphere);
        REQUIRE(shadedColor == Color::createGrey(0.0f));
    }SECTION("colorForLightIsWhite") {
        Color shadedColor = lambertMethod.lambertShading(Vector3f(1, 0, 0), *sphere);
        REQUIRE(shadedColor == Color::createWhite());
    }

    SECTION("lightIntensityIsApplied") {
        light->setIntensity(2);
        Color shadedColor = lambertMethod.lambertShading(Vector3f(1, 0, 0), *sphere);
        REQUIRE(shadedColor == Color::createGrey(2));
    }

    SECTION("noNegativeColorsAreProduced") {
        Color shadedColor = lambertMethod.colorForLight(Vector3f(-1, 0, 0), Vector3f(-1, 0, 0), scene.lights[0]);

        REQUIRE(shadedColor.r >= 0);
        REQUIRE(shadedColor.g >= 0);
        REQUIRE(shadedColor.b >= 0);
    }

    SECTION("everyLightIsConsidered") {
        std::shared_ptr<Light> light2 = std::make_shared<Light>(Transform::withPosition(Vector3f(-5, 0, 0)), 1);
        scene.addLight(light2);

        // we have one light on each side of the sphere on the x axis,
        // so on both sides color should be white
        Color shadedColor = lambertMethod.lambertShading(Vector3f(1, 0, 0), *sphere);
        REQUIRE(shadedColor == Color::createWhite());

        Color shadedColor2 = lambertMethod.lambertShading(Vector3f(-1, 0, 0), *sphere);
        REQUIRE(shadedColor2 == Color::createWhite());
    }
}
TEST_CASE("ShadingMethod/noLightsInSceneReturnsAmbientColor") {
    Scene scene2;
    std::shared_ptr<Sphere> sphere2 = std::make_shared<Sphere>(Vector3f(), 1);
    std::shared_ptr<DiffuseMaterial>
        defaultMaterial = std::make_shared<DiffuseMaterial>("defaultMaterial", Color::createWhite());
    sphere2->setMaterial(defaultMaterial);
    scene2.addObject(sphere2);
    ShadingMethod shadingMethod2(scene2);

    Color shadedColor = shadingMethod2.lambertShading(Vector3f(-1, 0, 0), *sphere2);
    REQUIRE(shadedColor == Color::createGrey(0.0f));
}
