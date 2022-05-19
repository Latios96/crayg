//
// Created by Jan Honsbrok on 25.11.18.
//

#include "sceneIO/read/usd/UsdSceneReader.h"
#include "UsdStageTranslator.h"
#include <pxr/usd/usd/stage.h>

namespace crayg {

UsdSceneReader::UsdSceneReader(const std::string &path, Scene &scene, const SceneReader::ReadOptions &readOptions)
    : SceneReader(path, scene, readOptions) {

}

void UsdSceneReader::read() {
    auto stage = pxr::UsdStage::Open(path);
    UsdStageTranslator translator(*stage);
    translator.translateStageToScene(scene, readOptions);
}

}
