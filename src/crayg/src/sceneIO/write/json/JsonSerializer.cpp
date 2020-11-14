//
// Created by Jan Honsbrok on 31.10.18.
//

#include "JsonSerializer.h"

#include <memory>

void JsonSerializer::startSceneObjects() {
    writer->Key("SceneObjects");
    writer->StartArray();
}

void JsonSerializer::endSceneObjects() {
    writer->EndArray();
}

void JsonSerializer::writeInt(std::string name, int value) {
    writer->Key(name.c_str());
    writer->Int(value);
}

void JsonSerializer::startObject() {
    writer->StartObject();
}

void JsonSerializer::endObject() {
    writer->EndObject();
}

void JsonSerializer::writeFloat(std::string name, float value) {
    writer->Key(name.c_str());
    writer->Double(value);
}

void JsonSerializer::writeVector3f(std::string name, Vector3f value) {
    writer->Key(name.c_str());
    writeVector3fImpl(value);
}

void JsonSerializer::writeVector3fImpl(const Vector3f &value) const {
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

JsonSerializer::JsonSerializer(std::shared_ptr<std::ostream> os) {
    os = os;
    osw = std::make_shared<rapidjson::OStreamWrapper>(*os);
    writer =
        std::make_shared<rapidjson::PrettyWriter<rapidjson::OStreamWrapper>>(
            *osw);
}

void JsonSerializer::writeVector3fArray(std::string name, std::vector<Vector3f> &value) {
    writer->Key(name.c_str());
    writer->StartArray();
    for (Vector3f vec : value) {
        writeVector3fImpl(vec);
    }
    writer->EndArray();
}

void JsonSerializer::writeIntArray(std::string name, std::vector<int> &value) {
    writer->Key(name.c_str());
    writer->StartArray();
    for (int i : value) {
        writer->Int(i);
    }
    writer->EndArray();
}
void JsonSerializer::writeFloatArray(std::string name, std::vector<float> &value) {
    writer->Key(name.c_str());
    writer->StartArray();
    for (int i : value) {
        writer->Double(i);
    }
    writer->EndArray();
}
void JsonSerializer::startCamera() {
    writer->Key("Camera");
}
void JsonSerializer::endCamera() {
}
void JsonSerializer::startRenderSettings() {
    writer->Key("RenderSettings");
}
void JsonSerializer::endRenderSettings() {
}
void JsonSerializer::start() {
    writer->StartObject();
}
void JsonSerializer::end() {
    writer->EndObject();
}
void JsonSerializer::writeMatrix4x4f(std::string name, Matrix4x4f matrix4X4f) {
    writer->Key(name.c_str());
    writer->StartArray();
    for (auto &row : matrix4X4f.values) {
        for (float column : row) {
            writer->Double(column);
        }
    }
    writer->EndArray();
}
void JsonSerializer::writeString(std::string name, std::string str) {
    writer->Key("type");
    writer->String(name.c_str());
}
