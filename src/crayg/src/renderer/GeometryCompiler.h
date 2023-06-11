#ifndef CRAYG_SRC_CRAYG_SRC_RENDERER_GEOMETRYCOMPILER_H_
#define CRAYG_SRC_CRAYG_SRC_RENDERER_GEOMETRYCOMPILER_H_

#include "scene/Scene.h"
#include "scene/primitives/subdivisionsurfacemesh/SubdivisionSurfaceMesh.h"
#include "utils/TaskReporter.h"

namespace crayg {

class GeometryCompiler {
  public:
    explicit GeometryCompiler(Scene &scene, TaskReporter &taskReporter);
    void compile();

  private:
    Scene &scene;
    TaskReporter &taskReporter;
    void tessellateSubdivisionSurfaces();
    void findAllSubdivisionSurfaceMeshes(std::vector<std::shared_ptr<SubdivisionSurfaceMesh>> &subdivisionSurfaces);
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_RENDERER_GEOMETRYCOMPILER_H_
