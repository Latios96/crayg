#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDSCENEWRITER_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDSCENEWRITER_H_

#include "UsdPathFactory.h"
#include "scene/Scene.h"
#include "sceneIO/usd/CraygUsdBase.h"
#include "sceneIO/write/SceneWriter.h"
#include <pxr/usd/usd/stage.h>
#include <string>

namespace crayg {

class UsdSceneWriter : public SceneWriter {
  public:
    UsdSceneWriter(Scene &scene);
    void writeScene(const std::string &scenePath) override;
    void writeScene(pxr::UsdStagePtr stage);
};

}

#endif // CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDSCENEWRITER_H_
