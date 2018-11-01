//
// Created by Jan Honsbrok on 30.10.18.
//

#ifndef CRAYG_SCENEWRITER_H
#define CRAYG_SCENEWRITER_H

#include "scene/Scene.h"
// todo add tests
class SceneWriter {
public:
    void write(std::string path);

    explicit SceneWriter(Scene &scene);

private:
    Scene& scene;
};


#endif //CRAYG_SCENEWRITER_H
