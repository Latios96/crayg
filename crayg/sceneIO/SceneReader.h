//
// Created by Jan Honsbrok on 31.10.18.
//

#ifndef CRAYG_SCENEREADER_H
#define CRAYG_SCENEREADER_H

static const char *const SCENE_OBJECTS = "SceneObjects";

static const char *const CAMERA = "Camera";

#include <scene/Scene.h>
#include "scene/TriangeMesh.h"
// todo add tests
// todo make more robust with error messages
class SceneReader {
public:
    void read(std::string path);

    explicit SceneReader(Scene &scene);

private:
    Scene& scene;
};


#endif //CRAYG_SCENEREADER_H
