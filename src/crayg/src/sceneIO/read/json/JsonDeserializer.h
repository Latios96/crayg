//
// Created by Jan Honsbrok on 31.10.18.
//

#ifndef CRAYG_JSONDESERIALIZER_H
#define CRAYG_JSONDESERIALIZER_H


#include <rapidjson/document.h>
#include "sceneIO/Serializable.h"

class JsonDeserializer : public Deserializer{
public:
    explicit JsonDeserializer(rapidjson::Value& jsonObject);

    int readInt(std::string name) override;
    float readFloat(std::string name) override;
    Vector3f readVector3f(std::string name) override;
    void readVector3fArray(std::string name, std::vector<Vector3f> &target) override;
    void readIntArray(std::string name, std::vector<int> &target) override;
private:
    rapidjson::Value& jsonObject;
};


#endif //CRAYG_JSONDESERIALIZER_H
