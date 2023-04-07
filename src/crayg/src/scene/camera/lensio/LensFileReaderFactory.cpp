#include "LensFileReaderFactory.h"
#include "LensFileTextFileReader.h"

namespace crayg {

std::unique_ptr<LensFileReader> LensFileReaderFactory::createLensFileReader(const std::string &filePath) {
    return std::make_unique<LensFileTextFileReader>();
}

std::unique_ptr<LensFileReader> LensFileReaderFactory::createLensFileReader(LensFileFormat lensFileFormat) {
    return std::make_unique<LensFileTextFileReader>();
}

} // crayg