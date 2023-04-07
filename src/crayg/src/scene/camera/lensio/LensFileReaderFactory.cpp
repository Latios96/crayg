#include "LensFileReaderFactory.h"
#include "LensFileJsonReader.h"
#include "LensFileTextFileReader.h"
#include "Logger.h"

namespace crayg {

std::unique_ptr<LensFileReader> LensFileReaderFactory::createLensFileReader(const std::string &filePath) {
    boost::filesystem::path path(filePath);
    std::string extension = path.extension().string();

    if (extension == ".txt") {
        return std::make_unique<LensFileTextFileReader>();
    } else if (extension == ".json") {
        return std::make_unique<LensFileJsonReader>();
    } else {
        Logger::error("No LensFileReader found for extension {}", extension);
        throw std::runtime_error(fmt::format("No LensFileReader found for extension {}", extension));
    }
}

std::unique_ptr<LensFileReader> LensFileReaderFactory::createLensFileReader(LensFileFormat lensFileFormat) {
    if (lensFileFormat == LensFileFormat::TXT) {
        return std::unique_ptr<LensFileTextFileReader>();
    } else if (lensFileFormat == LensFileFormat::JSON) {
        return std::unique_ptr<LensFileJsonReader>();
    } else {
        Logger::error("No LensFileReader found for extension {}", lensFileFormat);
        throw std::runtime_error(fmt::format("No LensFileReader found for extension {}", lensFileFormat));
    }
}

} // crayg