//
// Created by Jan Honsbrok on 25.11.18.
//

#include "JsonSceneReader.h"
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/document.h>
#include <fstream>
#include <scene/PointCloud.h>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem.hpp>
#include <scene/DiffuseMaterial.h>
#include "JsonDeserializer.h"
#include "utils/StopWatch.h"
#include "scene/Light.h"
#include "scene/GroundPlane.h"

JsonSceneReader::JsonSceneReader(const std::string &path, Scene &scene) : SceneReader(path, scene) {}

template<typename T>
void readSceneObject(Scene &scene, rapidjson::Value &obj) {
    std::shared_ptr<T> sphere = std::make_shared<T>();
    JsonDeserializer deserializer(obj);
    sphere->deserialize(deserializer);
    scene.addObject(sphere);
}

void readSceneObjects(Scene &scene, rapidjson::Document &d) {
    rapidjson::Value &sceneObjects = d[SCENE_OBJECTS];

    if (sceneObjects.IsArray()) {
        auto array = sceneObjects.GetArray();

        for (rapidjson::Value &obj : array) {
            std::string type(obj["type"].GetString());

            if (type == "Sphere") {
                readSceneObject<Sphere>(scene, obj);
            } else if (type == "GroundPlane") {
                readSceneObject<GroundPlane>(scene, obj);
            } else if (type == "TriangleMesh") {
                readSceneObject<TriangleMesh>(scene, obj);
            } else if (type == "PointCloud") {
                readSceneObject<PointCloud>(scene, obj);
            } else if (type == "Light") {
                std::shared_ptr<Light> light = std::make_shared<Light>();
                JsonDeserializer deserializer(obj);
                light->deserialize(deserializer);
                scene.addLight(light);
            } else if (type == "DiffuseMaterial") {
                std::shared_ptr<DiffuseMaterial> diffuseMaterial = std::make_shared<DiffuseMaterial>();
                JsonDeserializer deserializer(obj);
                diffuseMaterial->deserialize(deserializer);
                scene.addMaterial(diffuseMaterial);
            } else {
                Logger::warning("Unknown type {}", type);
            }
        }
    } else { // todo we can do this better
        throw
            SceneObjectsIsNotArray();
    }
}

void readCamera(Scene &scene, rapidjson::Document &d) {
    rapidjson::Value &cameraObject = d[CAMERA];

    if (cameraObject.IsObject()) {
        std::shared_ptr<Camera> camera = std::make_shared<Camera>();
        JsonDeserializer deserializer(cameraObject);
        camera->deserialize(deserializer);
        scene.camera = camera;
    }
}

void readRenderSettings(Scene &scene, rapidjson::Document &d) {
    rapidjson::Value &renderSettingsObject = d[RENDER_SETTINGS];

    if (renderSettingsObject.IsObject()) {
        int width = renderSettingsObject["width"].GetInt();
        int height = renderSettingsObject["height"].GetInt();
        int maxSamples = renderSettingsObject["maxSamples"].GetInt();
        RenderSettings renderSettings(Resolution(width, height), maxSamples);
        scene.renderSettings = renderSettings;
    }
}

struct DocumentValidationResult {
 public:
    const bool hasSceneObjects;
    const bool hasCamera;
    const bool hasRenderSettings;
    const bool hasMandatoryMembers;
};

DocumentValidationResult documentHasMandatoryMembers(rapidjson::Document &d) {
    const bool hasSceneObjects = d.HasMember(SCENE_OBJECTS);
    const bool hasCamera = d.HasMember(CAMERA);
    const bool hasRenderSettings = d.HasMember("RenderSettings");
    const bool hasMandatoryMembers = hasSceneObjects && hasCamera && hasRenderSettings;

    return {hasSceneObjects, hasCamera, hasRenderSettings, hasMandatoryMembers};
}

void JsonSceneReader::read() {
    boost::filesystem::path boostPath(path);
    if (!boost::filesystem::exists(boostPath)) {
        throw std::runtime_error(fmt::format("Could not read scene \"{}\", file does not exist!", path));
    }
    StopWatch stopwatch = StopWatch::createStopWatch("Scene reading");
    Logger::info("Reading scene {}", path);

    std::ifstream ifs(path);
    rapidjson::IStreamWrapper isw(ifs);
    rapidjson::Document document;
    document.ParseStream(isw);

    // validate
    auto result = documentHasMandatoryMembers(document);
    if (result.hasMandatoryMembers) {
        // now read the data
        readSceneObjects(scene, document);
        //TODO connectSceneObjectsToMaterials();
        readCamera(scene, document);
        readRenderSettings(scene, document);
    } else {
        //std::string message = "Error: scene misses following keys";

        const bool hasNoSceneObjects = result.hasSceneObjects == false;
        if (hasNoSceneObjects) {
            Logger::error("SceneObjects are missing!");
            throw SceneObjectsMissing();
        }

        const bool hasNoCamera = result.hasCamera == false;
        if (hasNoCamera) {
            Logger::error("Camera is missing!");
            throw CameraIsMissing();
        }

        const bool hasRenderSettings = result.hasRenderSettings == false;
        if (hasRenderSettings) {
            Logger::error("RenderSettings is missing!");
            throw RenderSettingsAreMissing();
        }

    }

    stopwatch.end();

}
