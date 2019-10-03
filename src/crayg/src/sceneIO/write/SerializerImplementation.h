//
// Created by Jan Honsbrok on 01.11.18.
//

#ifndef CRAYG_SERIALIZERIMPLEMENTATION_H
#define CRAYG_SERIALIZERIMPLEMENTATION_H

#include "sceneIO/Serializable.h"

class SerializerImplementation : public Serializer {
 public:
    virtual void init() = 0;
    virtual void startObject() = 0;
    virtual void endObject() = 0;
    virtual void finish() = 0;

    virtual ~SerializerImplementation() {

    };
};

#endif //CRAYG_SERIALIZERIMPLEMENTATION_H
