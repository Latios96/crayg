#pragma once

#include "scene/camera/realistic/lensio/LensFileReader.h"

namespace crayg {

class LensFileExtendedFormatReader : public LensFileReader {
  public:
    explicit LensFileExtendedFormatReader() = default;
    CameraLens readFileContent(const std::string &content) override;
};

} // crayg
