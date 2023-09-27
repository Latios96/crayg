#include "LensFileReaderFactory.h"
#include "Logger.h"
#include "extendedformat/LensFileExtendedFormatReader.h"
#include "textfile/LensFileTextFileReader.h"
#include "utils/Exceptions.h"
#include "json/LensFileJsonReader.h"
#include <boost/filesystem/path.hpp>

namespace crayg {

std::unique_ptr<LensFileReader> LensFileReaderFactory::createLensFileReader(const std::string &filePath) {
    boost::filesystem::path path(filePath);
    std::string extension = path.extension().string();

    if (extension == ".txt") {
        return std::make_unique<LensFileTextFileReader>();
    } else if (extension == ".json") {
        return std::make_unique<LensFileJsonReader>();
    } else if (extension == ".fx") {
        return std::make_unique<LensFileExtendedFormatReader>();
    } else {
        Logger::error("No LensFileReader found for extension {}", extension);
        CRAYG_LOG_AND_THROW(std::runtime_error(fmt::format("No LensFileReader found for extension {}", extension)));
    }
}

std::unique_ptr<LensFileReader> LensFileReaderFactory::createLensFileReader(LensFileFormat lensFileFormat) {
    if (lensFileFormat == LensFileFormat::TXT) {
        return std::make_unique<LensFileTextFileReader>();
    } else if (lensFileFormat == LensFileFormat::JSON) {
        return std::make_unique<LensFileJsonReader>();
    } else if (lensFileFormat == LensFileFormat::EXTENDED_FORMAT) {
        return std::make_unique<LensFileExtendedFormatReader>();
    } else {
        Logger::error("No LensFileReader found for extension {}", lensFileFormat);
        CRAYG_LOG_AND_THROW(
            std::runtime_error(fmt::format("No LensFileReader found for extension {}", lensFileFormat)));
    }
}

} // crayg