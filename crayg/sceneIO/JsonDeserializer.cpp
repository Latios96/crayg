//
// Created by Jan Honsbrok on 31.10.18.
//

#include <iostream>
#include "JsonDeserializer.h"
#define FMT_HEADER_ONLY
#include "fmt/format.h"

JsonDeserializer::JsonDeserializer(rapidjson::Value &jsonObject) : jsonObject(jsonObject) {}


int JsonDeserializer::readInt(std::string name) {
    if (jsonObject.HasMember(name.c_str())){
        return jsonObject[name.c_str()].GetInt();
    }
    else{
        std::cout << fmt::format("Could not read int with name '{}'", name) << std::endl;
        exit(-1);
    }
}

float JsonDeserializer::readFloat(std::string name) {
    if (jsonObject.HasMember(name.c_str())){
        return jsonObject[name.c_str()].GetFloat();
    }
    else{
        std::cout << fmt::format("Could not read float with name '{}'", name) << std::endl;
        exit(-1);
    }

}

Vector3f JsonDeserializer::readVector3f(std::string name) {
    if (jsonObject.HasMember(name.c_str())){
        const auto array = jsonObject[name.c_str()].GetArray();
        return {array[0].GetFloat(), array[1].GetFloat(), array[2].GetFloat()};
    }
    else{
        std::cout << fmt::format("Could not read Vector3f with name '{}'", name) << std::endl;
        exit(-1);
    }
}

void JsonDeserializer::readVector3fArray(std::string name, std::vector<Vector3f> &target) {
    if (jsonObject.HasMember(name.c_str())){
        const auto array = jsonObject[name.c_str()].GetArray();
        for(auto &vec3f : array){
            auto x = vec3f.GetArray()[0].GetFloat();
            auto y = vec3f.GetArray()[0].GetFloat();
            auto z = vec3f.GetArray()[0].GetFloat();
            target.push_back({x, y,z});
        }
    }
    else{
        std::cout << fmt::format("Could not read Vector3f Array with name '{}'", name) << std::endl;
        exit(-1);
    }
}

void JsonDeserializer::readIntArray(std::string name, std::vector<int> &target) {
    if (jsonObject.HasMember(name.c_str())){
        const auto array = jsonObject[name.c_str()].GetArray();
        for(auto &value : array){
            target.push_back(value.GetInt());
        }
    }
    else{
        std::cout << fmt::format("Could not read int Array with name '{}'", name) << std::endl;
        exit(-1);
    }
}
