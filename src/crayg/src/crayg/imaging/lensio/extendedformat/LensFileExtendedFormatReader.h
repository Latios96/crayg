#pragma once

#include "crayg/imaging/lensio/LensFileReader.h"

namespace crayg {

class LensFileExtendedFormatReader : public LensFileReader {
  public:
    explicit LensFileExtendedFormatReader() = default;
    CameraLens readFileContent(const std::string &content) override;
};

}
