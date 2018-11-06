//
// Created by Jan Honsbrok on 31.10.18.
//

#ifndef CRAYG_JSONSERIALIZER_H
#define CRAYG_JSONSERIALIZER_H


#include <fstream>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/prettywriter.h>
#include "Serializable.h"
#include "SerializerImplementation.h"

// todo add tests
class JsonSerializer : public SerializerImplementation{

public:
    explicit JsonSerializer(const std::string &path);

    void init() override;
    void startObject() override;
    void endObject() override;
    void finish() override;
    void writeInt(std::string name, int value) override;
    void writeFloat(std::string name, float value) override;
    void writeVector3f(std::string name, Vector3f value) override;
    void writeType(std::string name) override;

private:
    std::shared_ptr<std::ofstream> ofs;
    std::shared_ptr<rapidjson::OStreamWrapper> osw;
    std::shared_ptr<rapidjson::PrettyWriter<rapidjson::OStreamWrapper>> writer;
};



#endif //CRAYG_JSONSERIALIZER_H
