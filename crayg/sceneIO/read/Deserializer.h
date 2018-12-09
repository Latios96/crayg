//
// Created by Jan Honsbrok on 25.11.18.
//

#ifndef CRAYG_DESERIALIZER_H
#define CRAYG_DESERIALIZER_H

#include <string>
#include <vector>
#include <foundation/Vector3f.h>


class Deserializer{
public:
    virtual int readInt(std::string name)=0;
    virtual float readFloat(std::string name)=0;
    virtual Vector3f readVector3f(std::string name)=0;
    virtual void readVector3fArray(std::string name, std::vector<Vector3f> &target)=0;
    virtual void readIntArray(std::string name, std::vector<int> &target)=0;
};

#endif //CRAYG_DESERIALIZER_H
