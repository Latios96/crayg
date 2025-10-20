#pragma once
#include "crayg/imaging/lensio/LensFileReader.h"

namespace crayg {

class ZMXFileFormatReader : public LensFileReader {
  public:
    explicit ZMXFileFormatReader() = default;
    CameraLens readFileContent(const std::string &content) override;
};

}
