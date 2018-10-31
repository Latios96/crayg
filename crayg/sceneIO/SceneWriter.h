//
// Created by Jan Honsbrok on 30.10.18.
//

#ifndef CRAYG_SCENEWRITER_H
#define CRAYG_SCENEWRITER_H

#include "Scene.h"
class SceneWriter {
public:
    void write();

    explicit SceneWriter(Scene &scene);

private:
    Scene& scene;
};


#endif //CRAYG_SCENEWRITER_H
