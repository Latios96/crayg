//
// Created by jan on 29.12.18.
//
#include <catch.hpp>
#include <rapidjson/stream.h>
#include <rapidjson/document.h>
#include <sceneIO/read/json/JsonDeserializer.h>
#include <sceneIO/read/json/JsonSceneReader.h>
#include <fstream>

const char NO_SCENE_OBJECTS[] = R"({})";
const char NO_CAMERA[] = R"({"SceneObjects": []})";
const char SCENE_OBJECTS_IS_NOT_ARRAY[] = R"({"SceneObjects": 1, "Camera": {}})";

void writeFixture(const char* data, const std::string &path){
    std::ofstream out(path);
    out << data;
    out.close();
}

TEST_CASE("JsonSceneReader"){
    Scene scene;

    writeFixture(NO_SCENE_OBJECTS, "NO_SCENE_OBJECTS.json");
    writeFixture(NO_CAMERA, "NO_CAMERA.json");
    writeFixture(SCENE_OBJECTS_IS_NOT_ARRAY, "SCENE_OBJECTS_IS_NOT_ARRAY.json");


    SECTION("noSceneObjectsKeyShouldThrowException"){
        JsonSceneReader jsonSceneReader("NO_SCENE_OBJECTS.json", scene);
        REQUIRE_THROWS_AS(jsonSceneReader.read(), SceneObjectsMissing);
    }
    SECTION("noCameraShouldThrowException"){
        JsonSceneReader jsonSceneReader("NO_CAMERA.json", scene);
        REQUIRE_THROWS_AS(jsonSceneReader.read(), CameraIsMissing);
    }
    SECTION("noCameraShouldThrowException"){
        JsonSceneReader jsonSceneReader("SCENE_OBJECTS_IS_NOT_ARRAY.json", scene);
        REQUIRE_THROWS_AS(jsonSceneReader.read(), SceneObjectsIsNotArray);
    }

    remove("NO_SCENE_OBJECTS.json");
    remove("NO_CAMERA.json");
    remove("SCENE_OBJECTS_IS_NOT_ARRAY.json");
}

