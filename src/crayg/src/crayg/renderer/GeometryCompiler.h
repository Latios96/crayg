#pragma once

#include "crayg/foundation/progress/TaskReporter.h"
#include "crayg/scene/Scene.h"
#include "crayg/scene/primitives/subdivisionsurfacemesh/SubdivisionSurfaceMesh.h"

namespace crayg {

class GeometryCompiler {
  public:
    explicit GeometryCompiler(Scene &scene, BaseTaskReporter &taskReporter);
    void compile();

  private:
    Scene &scene;
    BaseTaskReporter &taskReporter;
    void tessellateSubdivisionSurfaces();
    void findAllSubdivisionSurfaceMeshes(std::vector<std::shared_ptr<SubdivisionSurfaceMesh>> &subdivisionSurfaces);
};

}
