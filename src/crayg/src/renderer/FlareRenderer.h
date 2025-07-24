#pragma once

#include "outputdrivers/NextGenOutputDriver.h"
#include "scene/Scene.h"
#include "utils/TaskReporter.h"

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
