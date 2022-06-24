#ifndef CRAYG_SCENECREATOR_H
#define CRAYG_SCENECREATOR_H

#include "Scene.h"

namespace crayg {

class SceneCreator {
    virtual void createScene(Scene &scene);
};

}
#endif //CRAYG_SCENECREATOR_H
