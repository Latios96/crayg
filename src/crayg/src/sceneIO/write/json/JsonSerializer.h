//
// Created by Jan Honsbrok on 31.10.18.
//

#ifndef CRAYG_JSONSERIALIZER_H
#define CRAYG_JSONSERIALIZER_H

#include <fstream>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/prettywriter.h>
#include "sceneIO/Serializable.h"
#include "sceneIO/write/SerializerImplementation.h"
#include <memory>

namespace crayg {

// todo add tests
class JsonSerializer : public SerializerImplementation {

 public:
    explicit JsonSerializer(std::shared_ptr<std::ostream> os);
    void start() override;
    void end() override;
    void startSceneObjects() override;
    void endSceneObjects() override;
    void startCamera() override;
    void endCamera() override;
    void startRenderSettings() override;
    void endRenderSettings() override;
    void startObject() override;
    void endObject() override;
    void writeInt(std::string name, int value) override;
    void writeFloat(std::string name, float value) override;
    void writeVector3f(std::string name, Vector3f value) override;
    void writeType(std::string name) override;
    void writeString(std::string name, std::string str) override;
    void writeVector3fArray(std::string name, std::vector<Vector3f> &value) override;
    void writeIntArray(std::string name, std::vector<int> &value) override;
    void writeFloatArray(std::string name, std::vector<float> &value) override;
    void writeMatrix4x4f(std::string name, Matrix4x4f matrix4X4f) override;
    void writeColor(std::string name, Color value) override;
 private:
    std::shared_ptr<std::ostream> os;
    std::shared_ptr<rapidjson::OStreamWrapper> osw;
    std::shared_ptr<rapidjson::PrettyWriter<rapidjson::OStreamWrapper>> writer;

    void writeVector3fImpl(const Vector3f &value) const;
};

}
#endif //CRAYG_JSONSERIALIZER_H
