//
// Created by Jan Honsbrok on 31.10.18.
//

#ifndef CRAYG_SCENEREADER_H
#define CRAYG_SCENEREADER_H

#include <Scene.h>

class SceneReader {
public:
    void read(std::string path);

    explicit SceneReader(Scene &scene);

private:
    Scene& scene;
};


#endif //CRAYG_SCENEREADER_H
