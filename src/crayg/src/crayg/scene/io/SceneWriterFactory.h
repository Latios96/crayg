#pragma once

#include "crayg/scene/io/write/SceneWriter.h"

namespace crayg {

class SceneWriterFactory {
  public:
    static std::shared_ptr<SceneWriter> createSceneWriter(std::string scenePath, Scene &scene);
};

}
