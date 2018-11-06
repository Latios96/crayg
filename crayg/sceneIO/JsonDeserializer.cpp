//
// Created by Jan Honsbrok on 31.10.18.
//

#include "JsonDeserializer.h"

JsonDeserializer::JsonDeserializer(rapidjson::Value &jsonObject) : jsonObject(jsonObject) {}

int JsonDeserializer::readInt(std::string name) {
    return jsonObject[name.c_str()].GetInt();
}

float JsonDeserializer::readFloat(std::string name) {
    return jsonObject[name.c_str()].GetFloat();
}

Vector3f JsonDeserializer::readVector3f(std::string name) {
    const auto array = jsonObject[name.c_str()].GetArray();
    return {array[0].GetFloat(), array[1].GetFloat(), array[2].GetFloat()};
}
