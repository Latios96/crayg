//
// Created by Jan Honsbrok on 31.10.18.
//

#ifndef CRAYG_SERIALIZABLE_H
#define CRAYG_SERIALIZABLE_H

#include <string>
#include "basics/Vector3f.h"
#include "sceneIO/write/Serializer.h"
#include "sceneIO/read/Deserializer.h"
#include <vector>

class Serializable {
 public:
    virtual void serialize(Serializer &serializer) = 0;
    virtual void deserialize(Deserializer &deserializer) = 0;
};

#endif //CRAYG_SERIALIZABLE_H
