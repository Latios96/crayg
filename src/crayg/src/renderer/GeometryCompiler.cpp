#include "GeometryCompiler.h"
#include "scene/primitives/PointInstancer.h"
#include "scene/primitives/subdivisionsurfacemesh/SubdivisionSurfaceMesh.h"
#include "utils/ProgressReporter.h"
#include <tbb/parallel_for.h>

namespace crayg {

GeometryCompiler::GeometryCompiler(Scene &scene, BaseTaskReporter &taskReporter)
    : scene(scene), taskReporter(taskReporter) {
}

void GeometryCompiler::compile() {
    tessellateSubdivisionSurfaces();
}

void GeometryCompiler::tessellateSubdivisionSurfaces() {
    std::vector<std::shared_ptr<SubdivisionSurfaceMesh>> subdivisionSurfaces;
    findAllSubdivisionSurfaceMeshes(subdivisionSurfaces);

    auto progressController = taskReporter.startTask("Compiling geometry", subdivisionSurfaces.size());

    tbb::parallel_for(static_cast<std::size_t>(0), subdivisionSurfaces.size(),
                      [&subdivisionSurfaces, &progressController](int i) {
                          subdivisionSurfaces[i]->tessellate();
                          progressController.iterationDone();
                      });
    progressController.finish();
}

void GeometryCompiler::findAllSubdivisionSurfaceMeshes(
    std::vector<std::shared_ptr<SubdivisionSurfaceMesh>> &subdivisionSurfaces) {
    for (auto &sceneObject : scene.objects) {
        if (sceneObject->getType() == "SubdivisionSurfaceMesh") {
            auto subdivisionSurfaceMesh = std::dynamic_pointer_cast<SubdivisionSurfaceMesh>(sceneObject);
            subdivisionSurfaces.push_back(subdivisionSurfaceMesh);
        } else if (sceneObject->getType() == "PointInstancer") {
            auto pointInstancer = std::dynamic_pointer_cast<PointInstancer>(sceneObject);
            for (auto &proto : pointInstancer->protos) {
                for (auto &member : proto->members) {
                    if (member->getType() == "SubdivisionSurfaceMesh") {
                        auto subdivisionSurfaceMesh = std::dynamic_pointer_cast<SubdivisionSurfaceMesh>(member);
                        subdivisionSurfaces.push_back(subdivisionSurfaceMesh);
                    }
                }
            }
        }
    }
}

} // crayg