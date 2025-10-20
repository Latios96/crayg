#pragma once

#include "crayg/imaging/lensio/LensFileWriter.h"

namespace crayg {

class LensFileExtendedFormatWriter : public LensFileWriter {
  public:
    std::string writeFileContent(const CameraLens &cameraLens) override;
};

}
