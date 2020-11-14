//
// Created by Jan Honsbrok on 25.11.18.
//

#ifndef CRAYG_SERIALIZER_H
#define CRAYG_SERIALIZER_H

#include <string>
#include <vector>
#include <basics/Vector3f.h>
#include <basics/Matrix4x4f.h>

class Serializer {
 public:
    virtual void writeInt(std::string name, int value) = 0;
    virtual void writeFloat(std::string name, float value) = 0;
    virtual void writeVector3f(std::string name, Vector3f value) = 0;
    virtual void writeType(std::string name) = 0;
    virtual void writeString(std::string name, std::string str) = 0;
    virtual void writeVector3fArray(std::string name, std::vector<Vector3f> &value) = 0;
    virtual void writeIntArray(std::string name, std::vector<int> &value) = 0;
    virtual void writeFloatArray(std::string name, std::vector<float> &value) = 0;
    virtual void writeMatrix4x4f(std::string name, Matrix4x4f matrix4X4f) = 0;
};

#endif //CRAYG_SERIALIZER_H
