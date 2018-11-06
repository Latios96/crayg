//
// Created by Jan Honsbrok on 31.10.18.
//

#ifndef CRAYG_SCENEREADER_H
#define CRAYG_SCENEREADER_H

#include <scene/Scene.h>
// todo add tests
// todo make more robust with error messages
// todo make template class, so we can better test it
class SceneReader {
public:
    void read(std::string path);

    explicit SceneReader(Scene &scene);

private:
    Scene& scene;
};


#endif //CRAYG_SCENEREADER_H
