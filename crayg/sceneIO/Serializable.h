//
// Created by Jan Honsbrok on 31.10.18.
//

#ifndef CRAYG_SERIALIZABLE_H
#define CRAYG_SERIALIZABLE_H

#include <string>
#include "foundation/Vector3f.h"

class Serializer{
public:
    virtual void writeInt(std::string name, int value)=0;
    virtual void writeFloat(std::string name, float value)=0;
    virtual void writeVector3f(std::string name, Vector3f value)=0;
    virtual void writeType(std::string name)=0;
};

class Deserializer{
public:
    virtual int readInt(std::string name)=0;
    virtual float readFloat(std::string name)=0;
    virtual Vector3f readVector3f(std::string name)=0;
};

class Serializable{
public:
    virtual void serialize(Serializer& serializer)=0;
    virtual void deserialize(Deserializer& deserializer)=0;
};



#endif //CRAYG_SERIALIZABLE_H
