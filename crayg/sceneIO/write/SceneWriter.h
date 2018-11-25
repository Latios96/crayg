//
// Created by Jan Honsbrok on 30.10.18.
//

#ifndef CRAYG_SCENEWRITER_H
#define CRAYG_SCENEWRITER_H

#include <utils/StopWatch.h>
#include "scene/Scene.h"
#include "sceneIO/write/json/JsonSerializer.h"

class SceneWriter {
public:
    void write();

    explicit SceneWriter(Scene &scene, SerializerImplementation& serializerImpl) : scene(scene),
    serializerImpl(serializerImpl) {}
    // todo add a factory for a JsonSceneWriter, but somewhere else than here

private:
    Scene& scene;
    // todo use a shared_ptr for this
    SerializerImplementation& serializerImpl;
};

#endif //CRAYG_SCENEWRITER_H
