#pragma once

#include "crayg/foundation/progress/TaskReporter.h"
#include "crayg/scene/Scene.h"
#include "outputdrivers/NextGenOutputDriver.h"

namespace crayg {

class FlareRenderer {
  public:
    FlareRenderer(Scene &scene, NextGenOutputDriver &outputDriver, BaseTaskReporter &taskReporter);

    void initialize();
    void renderScene();

  private:
    Scene &scene;
    NextGenOutputDriver &outputDriver;
    BaseTaskReporter &taskReporter;
};

}
