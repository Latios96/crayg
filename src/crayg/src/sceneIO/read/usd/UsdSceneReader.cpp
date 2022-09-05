#include "sceneIO/read/usd/UsdSceneReader.h"
#include "UsdStageReader.h"
#include "utils/StopWatch.h"
#include <pxr/usd/usd/stage.h>

namespace crayg {

UsdSceneReader::UsdSceneReader(const std::string &path, Scene &scene, const SceneReader::ReadOptions &readOptions)
    : SceneReader(path, scene, readOptions) {

}

void UsdSceneReader::read() {
    InformativeScopedStopWatch informativeScopedStopWatch(fmt::format("Reading USD Stage {}", path));
    auto stage = pxr::UsdStage::Open(path);
    UsdStageReader translator(*stage);
    translator.readStageToScene(scene, readOptions);
}

}
