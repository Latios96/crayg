//
// Created by Jan Honsbrok on 31.10.18.
//

#include <iostream>
#include "JsonDeserializer.h"
#include "fmt/format.h"

JsonDeserializer::JsonDeserializer(rapidjson::Value &jsonObject) : jsonObject(jsonObject) {}

template<typename T>
T JsonDeserializer::readValue(const std::string &name, std::function<T(rapidjson::Value &)> jsonValueConverter) {
    check_member_exists(name);
    return jsonValueConverter(jsonObject[name.c_str()]);
}

int JsonDeserializer::readInt(std::string name) {
    return readValue<int>(name, [](rapidjson::Value &value) { return value.GetInt(); });
}

float JsonDeserializer::readFloat(std::string name) {
    return readValue<float>(name, [](rapidjson::Value &value) { return value.GetFloat(); });
}

Vector3f JsonDeserializer::readVector3f(std::string name) {
    return readValue<Vector3f>(name, [](rapidjson::Value &value) {
        const auto array = value.GetArray();
        return Vector3f(array[0].GetFloat(), array[1].GetFloat(), array[2].GetFloat());
    });
}

void JsonDeserializer::readVector3fArray(std::string name, std::vector<Vector3f> &target) {
    check_member_exists(name);
    const auto array = jsonObject[name.c_str()].GetArray();
    for (auto &vec3f : array) {
        auto x = vec3f.GetArray()[0].GetFloat();
        auto y = vec3f.GetArray()[1].GetFloat();
        auto z = vec3f.GetArray()[2].GetFloat();
        target.emplace_back(x, y, z);
    }
}

void JsonDeserializer::readIntArray(std::string name, std::vector<int> &target) {
    check_member_exists(name);
    const auto array = jsonObject[name.c_str()].GetArray();
    for (auto &value : array) {
        target.push_back(value.GetInt());
    }
}
void JsonDeserializer::readFloatArray(std::string name, std::vector<float> &target) {
    check_member_exists(name);
    const auto array = jsonObject[name.c_str()].GetArray();
    for (auto &value : array) {
        target.push_back(value.GetFloat());
    }
}
bool JsonDeserializer::hasProperty(std::string name) {
    return jsonObject.HasMember(name.c_str());
}
Matrix4x4f JsonDeserializer::readMatrix4x4f(std::string name) {
    return readValue<Matrix4x4f>(name, [](rapidjson::Value &value) {
        float values[4][4];
        const auto array = value.GetArray();
        if (array.Size() != 16) {
            throw std::invalid_argument(fmt::format("Could not read Matrix4x4f, array has {} values", array.Size()));
        }
        return Matrix4x4f(array[0].GetFloat(),
                          array[1].GetFloat(),
                          array[2].GetFloat(),
                          array[3].GetFloat(),
                          array[4].GetFloat(),
                          array[5].GetFloat(),
                          array[6].GetFloat(),
                          array[7].GetFloat(),
                          array[8].GetFloat(),
                          array[9].GetFloat(),
                          array[10].GetFloat(),
                          array[11].GetFloat(),
                          array[12].GetFloat(),
                          array[13].GetFloat(),
                          array[14].GetFloat(),
                          array[15].GetFloat());
    });

}
std::string JsonDeserializer::readString(std::string name) {
    return readValue<std::string>(name, [](rapidjson::Value &value) { return value.GetString(); });

}
void JsonDeserializer::check_member_exists(const std::string &name) const {
    if (!jsonObject.HasMember(name.c_str())) {
        throw std::invalid_argument(fmt::format("Could not read member with name '{}'", name));
    }
}
Color JsonDeserializer::readColor(std::string name) {
    return readValue<Color>(name, [](rapidjson::Value &value) {
        const auto array = value.GetArray();
        return Color(array[0].GetFloat(), array[1].GetFloat(), array[2].GetFloat());
    });
}


