//
// Created by Jan Honsbrok on 25.11.18.
//

#include "JsonSceneReader.h"
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/document.h>
#include <fstream>
#include "JsonDeserializer.h"
#include "utils/StopWatch.h"
#include "scene/Light.h"
#include "scene/GroundPlane.h"

JsonSceneReader::JsonSceneReader(const std::string &path, Scene &scene) : SceneReader(path, scene) {}

void readSceneObjects(Scene &scene, rapidjson::Document &d){
    rapidjson::Value& sceneObjects = d[SCENE_OBJECTS];

    if (sceneObjects.IsArray()){
        auto array = sceneObjects.GetArray();

        for(rapidjson::Value& obj : array){
            // read type
            std::string type(obj["type"].GetString());

            if (type == "Sphere"){
                Sphere* sphere(new Sphere());
                JsonDeserializer deserializer(obj);
                sphere->deserialize(deserializer);
                scene.addObject(sphere);
            }
            else if (type == "GroundPlane"){
                GroundPlane* plane = new GroundPlane();
                JsonDeserializer deserializer(obj);
                plane->deserialize(deserializer);
                scene.addObject(plane);
            }
            else if (type == "TriangleMesh"){
                TriangleMesh* mesh = new TriangleMesh();
                JsonDeserializer deserializer(obj);
                mesh->deserialize(deserializer);
                scene.addObject(mesh);
            }
            else if (type == "Light"){
                Light* light = new Light();
                JsonDeserializer deserializer(obj);
                light->deserialize(deserializer);
                scene.addLight(light);
            }
            else{
                std::cout << fmt::format("Unknown type {}", type);
            }
        }
    }
    else{
        throw SceneObjectsIsNotArray();
    }
}

void readCamera(Scene &scene, rapidjson::Document &d){
    rapidjson::Value& cameraObject = d[CAMERA];

    if (cameraObject.IsObject()){
        Camera* camera = new Camera();
        JsonDeserializer deserializer(cameraObject);
        camera->deserialize(deserializer);
        scene.camera = camera;
    }

}

struct DocumentValidationResult{
public:
    const bool hasSceneObjects;
    const bool hasCamera;
    const bool hasMandatoryMembers;
};

DocumentValidationResult documentHasMandatoryMembers(rapidjson::Document &d){
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
    if(result.hasMandatoryMembers){
        // now read the data
        readSceneObjects(scene, document);

        readCamera(scene, document);
    }
    else{
        //std::string message = "Error: scene misses following keys";

        const bool hasNoSceneObjects = result.hasSceneObjects == false;
        if(hasNoSceneObjects){
            throw SceneObjectsMissing();
        }

        const bool hasNoCamera = result.hasCamera == false;
        if(hasNoCamera){
            throw CameraIsMissing();
        }

    }

    stopwatch.end();

}
