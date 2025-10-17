#include "sceneIO/read/usd/UsdSceneReader.h"
#include "UsdStageReader.h"
#include "crayg/foundation/progress/StopWatch.h"
#include "crayg/foundation/tracing/CraygTracing.h"
#include <pxr/usd/usd/stage.h>

namespace crayg {

UsdSceneReader::UsdSceneReader(const std::string &path, Scene &scene, const SceneReader::ReadOptions &readOptions)
    : SceneReader(path, scene, readOptions) {
}

void UsdSceneReader::read() {
    CRAYG_TRACE_SCOPE("UsdSceneReader");
    InformativeScopedStopWatch informativeScopedStopWatch(fmt::format("Reading USD Stage {}", path));
    auto stage = pxr::UsdStage::Open(path);
    UsdStageReader translator(*stage);
    translator.readStageToScene(scene, readOptions);
}

}
