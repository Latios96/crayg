//
// Created by jan on 29.12.18.
//
#include <catch2/catch.hpp>
#include <rapidjson/stream.h>
#include <rapidjson/document.h>
#include <sceneIO/read/json/JsonDeserializer.h>
#include <sceneIO/read/json/JsonSceneReader.h>
#include <fstream>

namespace crayg {

const char NO_SCENE_OBJECTS[] = R"({})";
const char NO_CAMERA[] = R"({"SceneObjects": [],"RenderSettings": {}})";
const char SCENE_OBJECTS_IS_NOT_ARRAY[] = R"({"SceneObjects": 1, "Camera": {},"RenderSettings": {}})";
const char NO_RENDER_SETTINGS[] = R"({"SceneObjects": [], "Camera": {}})";
const char CORRECT_SCENE[] = R"({
    "SceneObjects": [
        {
            "position": [
                0.0,
                0.0,
                0.0
            ],
            "type": "Sphere",
            "radius": 1.5,
            "material": "diffuseMaterial"
        },
        {
            "position": [
                0.0,
                3.0,
                3.0
            ],
            "type": "Light",
            "intensity": 1.0
        },
        {
            "position": [
                0.0,
                -1.5,
                0.0
            ],
            "type": "GroundPlane"
        },
        {
            "name": "diffuseMaterial",
            "type": "DiffuseMaterial",
            "diffuseColor": [
                0.5,
                0.5,
                0.5
            ]
        },
        {
            "position": [
                0.0,
                0.0,
                0.0
            ],
            "type": "Sphere",
            "radius": 1.5
        }
    ],
    "Camera": {
        "position": [
            0,
            0,
            10
        ],
        "centerOfInterest": [
            0,0,-1
        ],
        "userUpVector": [
            0.0,
            1.0,
            0.0
        ],
        "focalLength": 35.0,
        "filmbackSize": 36.0,
        "type": "Camera"
    },
    "RenderSettings": {
    "width": 800,
    "height": 600,
    "maxSamples": 4
  }})";

void writeFixture(const char *data, const std::string &path) {
    std::ofstream out(path);
    out << data;
    out.close();
}

TEST_CASE("JsonSceneReader") {
    Scene scene;

    writeFixture(NO_SCENE_OBJECTS, "NO_SCENE_OBJECTS.json");
    writeFixture(NO_CAMERA, "NO_CAMERA.json");
    writeFixture(SCENE_OBJECTS_IS_NOT_ARRAY, "SCENE_OBJECTS_IS_NOT_ARRAY.json");
    writeFixture(NO_RENDER_SETTINGS, "NO_RENDER_SETTINGS.json");
    writeFixture(CORRECT_SCENE, "CORRECT_SCENE.json");

    SECTION("noSceneObjectsKeyShouldThrowException") {
        JsonSceneReader jsonSceneReader("NO_SCENE_OBJECTS.json", scene);
        REQUIRE_THROWS_AS(jsonSceneReader.read(), SceneObjectsMissing);
    }

    SECTION("noCameraShouldThrowException") {
        JsonSceneReader jsonSceneReader("NO_CAMERA.json", scene);
        REQUIRE_THROWS_AS(jsonSceneReader.read(), CameraIsMissing);
    }

    SECTION("noCameraShouldThrowException") {
        JsonSceneReader jsonSceneReader("SCENE_OBJECTS_IS_NOT_ARRAY.json", scene);
        REQUIRE_THROWS_AS(jsonSceneReader.read(), SceneObjectsIsNotArray);
    }

    SECTION("noRenderSettingsShouldThrowException") {
        JsonSceneReader jsonSceneReader("NO_RENDER_SETTINGS.json", scene);
        REQUIRE_THROWS_AS(jsonSceneReader.read(), RenderSettingsAreMissing);
    }

    SECTION("shouldReadSceneCorrectly") {
        JsonSceneReader jsonSceneReader("CORRECT_SCENE.json", scene);
        jsonSceneReader.read();

        REQUIRE(scene.objects.size() == 3);
        REQUIRE(scene.objects[1]->getPosition() == Vector3f(0, -1.5f, 0));
        REQUIRE(scene.materials.size() == 2);
        REQUIRE(scene.objects[0]->getMaterial() == scene.materials[1]);
        REQUIRE(scene.objects[1]->getMaterial() == scene.materials[0]);
        REQUIRE(scene.objects[1]->getMaterial()->getName() == "defaultMaterial");
        REQUIRE(scene.camera->getPosition() == Vector3f(0, 0, 10));
        REQUIRE(scene.renderSettings.resolution == Resolution(800, 600));
        REQUIRE(scene.renderSettings.maxSamples == 4);
    }

    remove("NO_SCENE_OBJECTS.json");
    remove("NO_CAMERA.json");
    remove("SCENE_OBJECTS_IS_NOT_ARRAY.json");
    remove("NO_RENDER_SETTINGS.json");
    remove("CORRECT_SCENE.json");
}

TEST_CASE("JsonSceneReader not existing file should throw") {
    Scene scene;
    JsonSceneReader jsonSceneReader("aer.json", scene);

    REQUIRE_THROWS_AS(jsonSceneReader.read(), std::runtime_error);
}

}
