#pragma once

#include "LensFileFormat.h"
#include "LensFileWriter.h"
#include <memory>
#include <string>

namespace crayg {

class LensFileWriterFactory {
  public:
    static std::unique_ptr<LensFileWriter> createLensFileWriter(const std::string &filePath);
    static std::unique_ptr<LensFileWriter> createLensFileWriter(LensFileFormat lensFileFormat);
};

} // crayg
