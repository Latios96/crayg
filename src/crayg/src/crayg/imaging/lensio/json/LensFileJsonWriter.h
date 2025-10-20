#pragma once

#include "crayg/imaging/lensio/LensFileWriter.h"

namespace crayg {

class LensFileJsonWriter : public LensFileWriter {
  public:
    std::string writeFileContent(const CameraLens &cameraLens) override;
};

}
