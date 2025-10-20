#pragma once

#include "crayg/imaging/CameraLens.h"
#include <string>
#include <vector>

namespace crayg {

class LensFileReader {
  public:
    explicit LensFileReader() = default;

    virtual CameraLens readFile(const std::string &filePath);

    virtual CameraLens readFileContent(const std::string &content) = 0;

    virtual ~LensFileReader() = default;
};

}
