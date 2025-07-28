#pragma once

#include "LensFileFormat.h"
#include "LensFileReader.h"
#include <memory>

namespace crayg {

class LensFileReaderFactory {
  public:
    static std::unique_ptr<LensFileReader> createLensFileReader(const std::string &filePath);
    static std::unique_ptr<LensFileReader> createLensFileReader(LensFileFormat lensFileFormat);
};
}
