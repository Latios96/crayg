#pragma once

#include "sceneIO/read/SceneReader.h"

namespace crayg {

class UsdSceneReader : public SceneReader {
  public:
    UsdSceneReader(const std::string &path, Scene &scene, const ReadOptions &readOptions = ReadOptions::empty());

    void read() override;
};

}
