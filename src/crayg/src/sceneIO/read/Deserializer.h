//
// Created by Jan Honsbrok on 25.11.18.
//

#ifndef CRAYG_DESERIALIZER_H
#define CRAYG_DESERIALIZER_H

#include <string>
#include <vector>
#include <basics/Vector3f.h>
#include <basics/Matrix4x4f.h>
#include <basics/Color.h>

namespace crayg {

class Deserializer {
 public:
    virtual bool hasProperty(std::string name) = 0;
    virtual int readInt(std::string name) = 0;
    virtual float readFloat(std::string name) = 0;
    virtual std::string readString(std::string name) = 0;
    virtual Vector3f readVector3f(std::string name) = 0;
    virtual Matrix4x4f readMatrix4x4f(std::string name) = 0;
    virtual void readVector3fArray(std::string name, std::vector<Vector3f> &target) = 0;
    virtual void readIntArray(std::string name, std::vector<int> &target) = 0;
    virtual void readFloatArray(std::string name, std::vector<float> &target) = 0;
    virtual Color readColor(std::string name) = 0;

    virtual int readIntWithDefault(std::string name, int defaultValue) = 0;
    virtual float readFloatWithDefault(std::string name, float defaultValue) = 0;
    virtual std::string readStringWithDefault(std::string name, std::string defaultValue) = 0;
    virtual Vector3f readVector3fWithDefault(std::string name, Vector3f defaultValue) = 0;
    virtual Matrix4x4f readMatrix4x4fWithDefault(std::string name, Matrix4x4f defaultValue) = 0;
    virtual Color readColorWithDefault(std::string name, Color defaultValue) = 0;
};

}

#endif //CRAYG_DESERIALIZER_H
