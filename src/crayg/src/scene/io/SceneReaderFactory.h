#pragma once

#include <memory>
#include <scene/io/read/SceneReader.h>

namespace crayg {

class SceneReaderFactory {
  public:
    static std::shared_ptr<SceneReader>
    createSceneReader(const std::string &scenePath, Scene &scene,
                      const SceneReader::ReadOptions &readOptions = SceneReader::ReadOptions::empty());
};

}
