//
// Created by Jan on 02.06.2022.
//

#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDSCENEWRITER_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDSCENEWRITER_H_

#include <string>
#include "scene/Scene.h"
#include "sceneIO/usd/CraygUsdBase.h"
#include "UsdPathFactory.h"
#include "UsdMaterialWriteCache.h"
#include <pxr/usd/usd/stage.h>

namespace crayg {

class UsdSceneWriter {
 public:
    UsdSceneWriter(Scene &scene);
    void writeScene(const std::string &scenePath);
    void writeScene(pxr::UsdStagePtr stage);
 private:
    Scene &scene;
};

}

#endif //CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDSCENEWRITER_H_
