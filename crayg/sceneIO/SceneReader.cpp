//
// Created by Jan Honsbrok on 31.10.18.
//

#include <rapidjson/istreamwrapper.h>
#include <rapidjson/document.h>
#include <fstream>
#include "SceneReader.h"
#include "JsonDeserializer.h"

SceneReader::SceneReader(Scene &scene) : scene(scene) {}

void SceneReader::read(std::string path) {
    std::ifstream ifs(path);
    rapidjson::IStreamWrapper isw(ifs);
    rapidjson::Document d;
    d.ParseStream(isw);

    rapidjson::Value& sceneObjects = d["SceneObjects"];

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
            else{
                // todo unkown type
            }
        }
    }
    else{
        // todo error
    }


}
