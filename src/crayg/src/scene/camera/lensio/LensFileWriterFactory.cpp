#include "LensFileWriterFactory.h"
#include "LensFileTextFileWriter.h"

namespace crayg {
std::unique_ptr<LensFileWriter> LensFileWriterFactory::createLensFileWriter(const std::string &filePath) {
    return std::unique_ptr<LensFileTextFileWriter>();
}

std::unique_ptr<LensFileWriter> LensFileWriterFactory::createLensFileWriter(LensFileFormat lensFileFormat) {
    return std::unique_ptr<LensFileTextFileWriter>();
}
} // crayg