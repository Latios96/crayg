//
// Created by Jan Honsbrok on 31.10.18.
//

#ifndef CRAYG_SCENEREADER_H
#define CRAYG_SCENEREADER_H

#include <scene/Scene.h>
#include "scene/TriangleMesh.h"

class SceneReader {
public:
    virtual void read()=0;

    explicit SceneReader(std::string path, Scene &scene);

protected:
    Scene& scene;
    std::string path;
};


#endif //CRAYG_SCENEREADER_H
