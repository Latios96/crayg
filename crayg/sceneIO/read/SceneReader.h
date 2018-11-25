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
// todo take path with constructor
class SceneReader {
public:
    // todo make this virtual, create a factory with a method for a JsonSceneReader
    void read(std::string path);

    explicit SceneReader(Scene &scene);

private:
    Scene& scene;
};


#endif //CRAYG_SCENEREADER_H
