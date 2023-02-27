#ifndef CRAYG_SCENEWRITER_H
#define CRAYG_SCENEWRITER_H

#include "scene/Scene.h"
#include <utils/StopWatch.h>

namespace crayg {

class SceneWriter {
  public:
    SceneWriter(Scene &scene);
    virtual void writeScene(const std::string &scenePath) = 0;

  protected:
    Scene &scene;
};

}

#endif // CRAYG_SCENEWRITER_H
