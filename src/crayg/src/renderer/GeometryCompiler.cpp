#include <tbb/parallel_for.h>
#include "GeometryCompiler.h"
#include "scene/primitives/subdivisionsurfacemesh/SubdivisionSurfaceMesh.h"
#include "utils/ProgressReporter.h"

namespace crayg {

GeometryCompiler::GeometryCompiler(Scene &scene) : scene(scene) {}

void GeometryCompiler::compile() {
    tessellateSubdivisionSurfaces();
}
void GeometryCompiler::tessellateSubdivisionSurfaces() {
    std::vector<std::shared_ptr<SubdivisionSurfaceMesh>> subdivisionSurfaces;
    findAllSubdivisionSurfaceMeshes(subdivisionSurfaces);

    ProgressReporter reporter = ProgressReporter::createLoggingProgressReporter(static_cast<int>(subdivisionSurfaces.size()),
                                                                                "Compiling geometry");

    tbb::parallel_for(static_cast<std::size_t>(0),
                      subdivisionSurfaces.size(),
                      [&subdivisionSurfaces, &reporter](int i) {
                          subdivisionSurfaces[i]->tessellate();
                          reporter.iterationDone();
                      });
    reporter.finish();
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