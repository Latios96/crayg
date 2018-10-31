//
// Created by Jan Honsbrok on 31.10.18.
//

#ifndef CRAYG_JSONSERIALIZER_H
#define CRAYG_JSONSERIALIZER_H


#include <fstream>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/prettywriter.h>
#include "Serializable.h"
// todo add tests
class JsonSerializer : public Serializer{

public:
    explicit JsonSerializer(rapidjson::PrettyWriter<rapidjson::OStreamWrapper> &writer) : writer(writer) {}
    void init();
    void startObject();
    void endObject();
    void finish();
    void writeInt(std::string name, int value) override;
    void writeFloat(std::string name, float value) override;
    void writeVector3f(std::string name, Vector3f value) override;
    void writeType(std::string name) override;

private:
    rapidjson::PrettyWriter<rapidjson::OStreamWrapper>& writer;
};



#endif //CRAYG_JSONSERIALIZER_H
