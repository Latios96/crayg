#pragma once

#include "scene/camera/realistic/lensio/LensFileReader.h"

namespace crayg {

class LensFileJsonReader : public LensFileReader {
  public:
    CameraLens readFileContent(const std::string &content) override;
};

}
