#pragma once

#include "sceneIO/write/SceneWriter.h"

namespace crayg {

class SceneWriterFactory {
  public:
    static std::shared_ptr<SceneWriter> createSceneWriter(std::string scenePath, Scene &scene);
};

}
