#pragma once

#include "crayg/scene/camera/realistic/lensio/LensFileWriter.h"

namespace crayg {

class LensFileExtendedFormatWriter : public LensFileWriter {
  public:
    std::string writeFileContent(const CameraLens &cameraLens) override;
};

}
