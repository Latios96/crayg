//
// Created by Jan Honsbrok on 25.11.18.
//

#include "JsonSceneReader.h"
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/document.h>
#include <fstream>
#include <scene/PointCloud.h>
#include "JsonDeserializer.h"
#include "utils/StopWatch.h"
#include "scene/Light.h"
#include "scene/GroundPlane.h"

JsonSceneReader::JsonSceneReader(const std::string &path, Scene &scene) : SceneReader(path, scene) {}

void readSceneObjects(Scene &scene, rapidjson::Document &d) {
    rapidjson::Value &sceneObjects = d[SCENE_OBJECTS];

    if (sceneObjects.IsArray()) {
        auto array = sceneObjects.GetArray();

        for (rapidjson::Value &obj : array) {
            std::string type(obj["type"].GetString());

            if (type == "Sphere") {
                std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>();
                JsonDeserializer deserializer(obj);
                sphere->deserialize(deserializer);
                scene.addObject(sphere);
            } else if (type == "GroundPlane") {
                std::shared_ptr<GroundPlane> plane = std::make_shared<GroundPlane>();
                JsonDeserializer deserializer(obj);
                plane->deserialize(deserializer);
                scene.addObject(plane);
            } else if (type == "TriangleMesh") {
                std::shared_ptr<TriangleMesh> mesh = std::make_shared<TriangleMesh>();
                JsonDeserializer deserializer(obj);
                mesh->deserialize(deserializer);
                scene.addObject(mesh);
            } else if (type == "Light") {
                std::shared_ptr<Light> light = std::make_shared<Light>();
                JsonDeserializer deserializer(obj);
                light->deserialize(deserializer);
                scene.addLight(light);
            } else if (type == "PointCloud") {
                std::shared_ptr<PointCloud> pointCloud = std::make_shared<PointCloud>();
                JsonDeserializer deserializer(obj);
                pointCloud->deserialize(deserializer);
                scene.addObject(pointCloud);
            } else {
                Logger::warning("Unknown type {}", type);
            }
        }
    } else {
        throw SceneObjectsIsNotArray();
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

struct DocumentValidationResult {
 public:
    const bool hasSceneObjects;
    const bool hasCamera;
    const bool hasMandatoryMembers;
};

DocumentValidationResult documentHasMandatoryMembers(rapidjson::Document &d) {
    const bool hasSceneObjects = d.HasMember(SCENE_OBJECTS);
    const bool hasCamera = d.HasMember(CAMERA);
    const bool hasMandatoryMembers = hasSceneObjects && hasCamera;

    return {hasSceneObjects, hasCamera, hasMandatoryMembers};
}

void JsonSceneReader::read() {
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

        readCamera(scene, document);
    } else {
        //std::string message = "Error: scene misses following keys";

        const bool hasNoSceneObjects = result.hasSceneObjects == false;
        if (hasNoSceneObjects) {
            throw SceneObjectsMissing();
        }

        const bool hasNoCamera = result.hasCamera == false;
        if (hasNoCamera) {
            throw CameraIsMissing();
        }

    }

    stopwatch.end();

}
