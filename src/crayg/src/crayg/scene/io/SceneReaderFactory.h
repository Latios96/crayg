#pragma once

#include "crayg/scene/io/read/SceneReader.h"
#include <memory>

namespace crayg {

class SceneReaderFactory {
  public:
    static std::shared_ptr<SceneReader>
    createSceneReader(const std::string &scenePath, Scene &scene,
                      const SceneReader::ReadOptions &readOptions = SceneReader::ReadOptions::empty());
};

}
