//
// Created by Jan Honsbrok on 31.10.18.
//

#ifndef CRAYG_JSONDESERIALIZER_H
#define CRAYG_JSONDESERIALIZER_H

#include <rapidjson/document.h>
#include <functional>
#include "sceneIO/Serializable.h"

class JsonDeserializer : public Deserializer {
 public:
    explicit JsonDeserializer(rapidjson::Value &jsonObject);
    bool hasProperty(std::string name) override;
    int readInt(std::string name) override;
    float readFloat(std::string name) override;
    std::string readString(std::string name) override;
    Vector3f readVector3f(std::string name) override;
    Matrix4x4f readMatrix4x4f(std::string name) override;
    void readVector3fArray(std::string name, std::vector<Vector3f> &target) override;
    void readIntArray(std::string name, std::vector<int> &target) override;
    void readFloatArray(std::string name, std::vector<float> &target) override;
    Color readColor(std::string name) override;
 private:
    rapidjson::Value &jsonObject;
    void check_member_exists(const std::string &name) const;
    template<typename T>
    T readValue(const std::string &name);
    template<typename T>
    T convertJsonValue(const rapidjson::Value &value);
};

#endif //CRAYG_JSONDESERIALIZER_H
