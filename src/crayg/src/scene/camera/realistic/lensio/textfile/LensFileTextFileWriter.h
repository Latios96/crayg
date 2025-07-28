#pragma once

#include "scene/camera/realistic/lensio/LensFileWriter.h"

namespace crayg {

class LensFileTextFileWriter : public LensFileWriter {
  public:
    std::string writeFileContent(const CameraLens &cameraLens) override;
};

}
