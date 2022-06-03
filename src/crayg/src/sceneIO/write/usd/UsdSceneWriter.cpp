//
// Created by Jan on 02.06.2022.
//

#include "UsdSceneWriter.h"
#include "UsdCameraWriter.h"
#include "UsdRenderSettingsWriter.h"
#include "UsdSphereWriter.h"

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
        }
    }
    // write lights
}
