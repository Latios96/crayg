//
// Created by Jan Honsbrok on 30.10.18.
//

#ifndef CRAYG_SCENEWRITER_H
#define CRAYG_SCENEWRITER_H

#include <utils/StopWatch.h>
#include "scene/Scene.h"
#include "sceneIO/write/SerializerImplementation.h"

namespace crayg {

class SceneWriter {
 public:
    void write();

    explicit SceneWriter(Scene &scene, SerializerImplementation &serializerImpl) : scene(scene),
                                                                                   serializerImpl(serializerImpl) {}

 private:
    Scene &scene;
    SerializerImplementation &serializerImpl;
};

}

#endif //CRAYG_SCENEWRITER_H
