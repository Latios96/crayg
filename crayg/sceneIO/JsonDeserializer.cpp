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
