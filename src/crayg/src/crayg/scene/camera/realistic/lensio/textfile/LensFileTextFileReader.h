#pragma once

#include "crayg/scene/camera/realistic/lensio/LensFileReader.h"

namespace crayg {

class LensFileTextFileReader : public LensFileReader {
  public:
    explicit LensFileTextFileReader() = default;
    CameraLens readFileContent(const std::string &content) override;

  private:
    LensSurface readLensSurface(const std::string &line) const;
};

}
