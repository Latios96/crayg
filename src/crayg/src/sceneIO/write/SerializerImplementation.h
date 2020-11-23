//
// Created by Jan Honsbrok on 01.11.18.
//

#ifndef CRAYG_SERIALIZERIMPLEMENTATION_H
#define CRAYG_SERIALIZERIMPLEMENTATION_H

#include "sceneIO/Serializable.h"

namespace crayg {

class SerializerImplementation : public Serializer {
 public:
    virtual void start() = 0;
    virtual void end() = 0;
    virtual void startSceneObjects() = 0;
    virtual void endSceneObjects() = 0;
    virtual void startCamera() = 0;
    virtual void endCamera() = 0;
    virtual void startRenderSettings() = 0;
    virtual void endRenderSettings() = 0;
    virtual void startObject() = 0;
    virtual void endObject() = 0;

    virtual ~SerializerImplementation() = default;;
};

}

#endif //CRAYG_SERIALIZERIMPLEMENTATION_H
