#pragma once

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
