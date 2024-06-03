#pragma once

#include "scene/camera/realistic/lensio/LensFileReader.h"

namespace crayg {

class LensFileTextFileReader : public LensFileReader {
  public:
    explicit LensFileTextFileReader() = default;
    CameraLens readFileContent(const std::string &content) override;

  private:
    LensElement readLensElement(const std::string &line) const;
};

} // crayg
