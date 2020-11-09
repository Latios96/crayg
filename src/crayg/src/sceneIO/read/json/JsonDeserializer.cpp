//
// Created by Jan Honsbrok on 31.10.18.
//

#include <iostream>
#include "JsonDeserializer.h"
#include "fmt/format.h"

JsonDeserializer::JsonDeserializer(rapidjson::Value &jsonObject) : jsonObject(jsonObject) {}

int JsonDeserializer::readInt(std::string name) {
    if (jsonObject.HasMember(name.c_str())) {
        return jsonObject[name.c_str()].GetInt();
    } else {
        throw std::invalid_argument(fmt::format("Could not read int with name '{}'", name));
    }
}

float JsonDeserializer::readFloat(std::string name) {
    if (jsonObject.HasMember(name.c_str())) {
        return jsonObject[name.c_str()].GetFloat();
    } else {
        throw std::invalid_argument(fmt::format("Could not read float with name '{}'", name));
    }

}

Vector3f JsonDeserializer::readVector3f(std::string name) {
    if (jsonObject.HasMember(name.c_str())) {
        const auto array = jsonObject[name.c_str()].GetArray();
        return {array[0].GetFloat(), array[1].GetFloat(), array[2].GetFloat()};
    } else {
        throw std::invalid_argument(fmt::format("Could not read Vector3f with name '{}'", name));
    }
}

void JsonDeserializer::readVector3fArray(std::string name, std::vector<Vector3f> &target) {
    if (jsonObject.HasMember(name.c_str())) {
        const auto array = jsonObject[name.c_str()].GetArray();
        for (auto &vec3f : array) {
            auto x = vec3f.GetArray()[0].GetFloat();
            auto y = vec3f.GetArray()[1].GetFloat();
            auto z = vec3f.GetArray()[2].GetFloat();
            target.push_back({x, y, z});
        }
    } else {
        throw std::invalid_argument(fmt::format("Could not read Vector3f Array with name '{}'", name));
    }
}

void JsonDeserializer::readIntArray(std::string name, std::vector<int> &target) {
    if (jsonObject.HasMember(name.c_str())) {
        const auto array = jsonObject[name.c_str()].GetArray();
        for (auto &value : array) {
            target.push_back(value.GetInt());
        }
    } else {
        throw std::invalid_argument(fmt::format("Could not read int Array with name '{}'", name));
    }
}
void JsonDeserializer::readFloatArray(std::string name, std::vector<float> &target) {
    if (jsonObject.HasMember(name.c_str())) {
        const auto array = jsonObject[name.c_str()].GetArray();
        for (auto &value : array) {
            target.push_back(value.GetFloat());
        }
    } else {
        throw std::invalid_argument(fmt::format("Could not read float Array with name '{}'", name));
    }
}
bool JsonDeserializer::hasProperty(std::string name) {
    return jsonObject.HasMember(name.c_str());
}
