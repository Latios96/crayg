//
// Created by Jan Honsbrok on 31.10.18.
//

#include <rapidjson/istreamwrapper.h>
#include <rapidjson/document.h>
#include <fstream>
#include "SceneReader.h"
#include "JsonDeserializer.h"
#include "utils/StopWatch.h"
#include "scene/Light.h"
#include "scene/GroundPlane.h"


SceneReader::SceneReader(Scene &scene) : scene(scene) {}

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
            else if (type == "Light"){
                Light* light = new Light();
                JsonDeserializer deserializer(obj);
                light->deserialize(deserializer);
                scene.addLight(light);
            }
            else{
                // todo unknown type
            }
        }
    }
    else{
        // todo error
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

void SceneReader::read(std::string path) {
    StopWatch stopwatch("Scene reading");

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
        std::cout << "Error: scene misses following keys";
        if(result.hasCamera == false){
            std::cout << " \"Camera\"";
        }
        if(result.hasSceneObjects == false){
            std::cout << " \"SceneObjects\"";
        }
        std::cout << std::endl;
        exit(-2);
    }

    stopwatch.end();

}
