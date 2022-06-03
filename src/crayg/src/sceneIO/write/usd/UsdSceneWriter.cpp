//
// Created by Jan on 02.06.2022.
//

#include "UsdSceneWriter.h"
#include "UsdCameraWriter.h"
#include "UsdRenderSettingsWriter.h"

void crayg::UsdSceneWriter::writeScene(const std::string &scenePath, crayg::Scene &scene) {
    auto stage = pxr::UsdStage::CreateNew(scenePath);

    writeScene(stage, scene);

    stage->Save();
}
void crayg::UsdSceneWriter::writeScene(pxr::UsdStagePtr stage, crayg::Scene &scene) {
    UsdCameraWriter(scene.camera).write(stage, usdPathFactory);
    // todo tests
    UsdRenderSettingsWriter(scene.renderSettings).write(stage);

    // read lights
    // read objects with materials
}
