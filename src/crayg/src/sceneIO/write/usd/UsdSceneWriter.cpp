//
// Created by Jan on 02.06.2022.
//

#include "UsdSceneWriter.h"
#include "UsdCameraWriter.h"
#include "UsdRenderSettingsWriter.h"
#include "UsdSphereWriter.h"
#include "UsdPointLightWriter.h"
#include "UsdRectLightWriter.h"
#include "UsdDiskLightWriter.h"
#include "UsdTriangleMeshWriter.h"
#include "UsdGroundPlaneWriter.h"

void crayg::UsdSceneWriter::writeScene(const std::string &scenePath) {
    auto stage = pxr::UsdStage::CreateNew(scenePath);

    writeScene(stage);

    stage->Save();
}
void crayg::UsdSceneWriter::writeScene(pxr::UsdStagePtr stage) {
    UsdPathFactory usdPathFactory;
    UsdCameraWriter(scene.camera).write(stage, usdPathFactory);

    UsdRenderSettingsWriter(scene.renderSettings).write(stage);
    UsdMaterialWriteCache usdMaterialWriteCache(stage, usdPathFactory);

    for (auto sceneObject: scene.owningObjects) {
        if (sceneObject->getType() == "Sphere") {
            UsdSphereWriter(std::static_pointer_cast<Sphere>(sceneObject), usdMaterialWriteCache).write(stage,
                                                                                                        usdPathFactory);
        } else if (sceneObject->getType() == "TriangleMesh") {
            UsdTriangleMeshWriter(std::static_pointer_cast<TriangleMesh>(sceneObject), usdMaterialWriteCache).write(
                stage,
                usdPathFactory);
        } else if (sceneObject->getType() == "GroundPlane") {
            UsdGroundPlaneWriter(std::static_pointer_cast<GroundPlane>(sceneObject), usdMaterialWriteCache).write(stage,
                                                                                                                  usdPathFactory);
        } else {
            Logger::warning("Skipping unsupported type {}", sceneObject->getType());
        }
    }

    for (auto light: scene.lights) {
        if (light->getType() == "Light") {
            UsdPointLightWriter(std::static_pointer_cast<Light>(light)).write(stage, usdPathFactory);
        } else if (light->getType() == "RectLight") {
            UsdRectLightWriter(std::static_pointer_cast<RectLight>(light)).write(stage, usdPathFactory);
        } else if (light->getType() == "DiskLight") {
            UsdDiskLightWriter(std::static_pointer_cast<DiskLight>(light)).write(stage, usdPathFactory);
        } else {
            Logger::warning("Skipping unsupported type {}", light->getType());
        }
    }

}
crayg::UsdSceneWriter::UsdSceneWriter(crayg::Scene &scene) : scene(scene) {}
