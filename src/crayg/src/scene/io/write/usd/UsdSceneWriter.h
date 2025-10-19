#pragma once

#include "UsdPathFactory.h"
#include "scene/Scene.h"
#include "scene/io/write/SceneWriter.h"
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
