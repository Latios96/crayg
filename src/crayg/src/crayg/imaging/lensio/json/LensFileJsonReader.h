#pragma once

#include "crayg/imaging/lensio/LensFileReader.h"

namespace crayg {

class LensFileJsonReader : public LensFileReader {
  public:
    CameraLens readFileContent(const std::string &content) override;
};

}
