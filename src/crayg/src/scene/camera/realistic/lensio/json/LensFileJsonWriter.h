#pragma once

#include "scene/camera/realistic/lensio/LensFileWriter.h"

namespace crayg {

class LensFileJsonWriter : public LensFileWriter {
  public:
    std::string writeFileContent(const CameraLens &cameraLens) override;
};

}
