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

void crayg::UsdSceneWriter::writeScene(const std::string &scenePath, crayg::Scene &scene) {
    auto stage = pxr::UsdStage::CreateNew(scenePath);

    writeScene(stage, scene);

    stage->Save();
}
void crayg::UsdSceneWriter::writeScene(pxr::UsdStagePtr stage, crayg::Scene &scene) {
    UsdCameraWriter(scene.camera).write(stage, usdPathFactory);

    UsdRenderSettingsWriter(scene.renderSettings).write(stage);

    for (auto sceneObject: scene.owningObjects) {
        if (sceneObject->getType() == "Sphere") {
            UsdSphereWriter(std::static_pointer_cast<Sphere>(sceneObject)).write(stage, usdPathFactory);
        } else if (sceneObject->getType() == "TriangleMesh") {
            UsdTriangleMeshWriter(std::static_pointer_cast<TriangleMesh>(sceneObject)).write(stage, usdPathFactory);
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
