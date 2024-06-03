#pragma once

#include "scene/camera/realistic/lensio/LensFileReader.h"

namespace crayg {

class LensFileExtendedFormatReader : public LensFileReader {
  public:
    explicit LensFileExtendedFormatReader() = default;
    CameraLens readFileContent(const std::string &content) override;

    CameraLensMetadata parseMetadata(const std::vector<std::string> &lines);
    std::vector<LensElement> parseElements(const std::vector<std::string> &lines);
};

} // crayg
