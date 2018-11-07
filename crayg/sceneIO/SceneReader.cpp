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


void SceneReader::read(std::string path) {
    StopWatch stopwatch("Scene reading");

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

    stopwatch.end();


}
