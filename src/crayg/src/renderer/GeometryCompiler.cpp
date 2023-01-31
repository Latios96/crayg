#include <tbb/parallel_for.h>
#include "GeometryCompiler.h"
#include "scene/primitives/subdivisionsurfacemesh/SubdivisionSurfaceMesh.h"
#include "utils/StopWatch.h"

namespace crayg {

GeometryCompiler::GeometryCompiler(Scene &scene) : scene(scene) {}

void GeometryCompiler::compile() {
    InformativeScopedStopWatch buildBvh("Compiling geometry");
    tessellateSubdivisionSurfaces();
}
void GeometryCompiler::tessellateSubdivisionSurfaces() {
    std::vector<std::shared_ptr<SubdivisionSurfaceMesh>> subdivisionSurfaces;
    findAllSubdivisionSurfaceMeshes(subdivisionSurfaces);

    tbb::parallel_for(static_cast<std::size_t>(0),
                      subdivisionSurfaces.size(),
                      [&subdivisionSurfaces](int i) {
                          subdivisionSurfaces[i]->tessellate();
                      });
}
void GeometryCompiler::findAllSubdivisionSurfaceMeshes(std::vector<std::shared_ptr<SubdivisionSurfaceMesh>> &subdivisionSurfaces) {
    for(auto &sceneObject : scene.objects){
        if(sceneObject->getType() == "SubdivisionSurfaceMesh"){
            auto subdivisionSurfaceMesh = std::dynamic_pointer_cast<SubdivisionSurfaceMesh>(sceneObject);
            subdivisionSurfaces.push_back(subdivisionSurfaceMesh);
        }
    }
}

} // crayg