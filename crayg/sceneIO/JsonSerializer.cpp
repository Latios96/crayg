//
// Created by Jan Honsbrok on 31.10.18.
//

#include "JsonSerializer.h"

void JsonSerializer::init() {
    writer->StartObject();
    writer->Key("SceneObjects");
    writer->StartArray();
}

void JsonSerializer::startObject() {
    writer->StartObject();
}

void JsonSerializer::endObject() {
    writer->EndObject();
}

void JsonSerializer::finish() {
    writer->EndArray();
    writer->EndObject();
    ofs->close();
}

void JsonSerializer::writeInt(std::string name, int value) {
    writer->Key(name.c_str());
    writer->Int(value);
}

void JsonSerializer::writeFloat(std::string name, float value) {
    writer->Key(name.c_str());
    writer->Double(value);
}

void JsonSerializer::writeVector3f(std::string name, Vector3f value) {
    writer->Key(name.c_str());
    writer->StartArray();
    writer->Double(value.x);
    writer->Double(value.y);
    writer->Double(value.z);
    writer->EndArray();
}

void JsonSerializer::writeType(std::string name) {
    writer->Key("type");
    writer->String(name.c_str());
}

JsonSerializer::JsonSerializer(const std::string &path){
    ofs = std::shared_ptr<std::ofstream>(new std::ofstream(path));
    osw = std::shared_ptr<rapidjson::OStreamWrapper>(new rapidjson::OStreamWrapper(*ofs));
    writer = std::shared_ptr<rapidjson::PrettyWriter<rapidjson::OStreamWrapper>>(new rapidjson::PrettyWriter<rapidjson::OStreamWrapper>(*osw));
}
