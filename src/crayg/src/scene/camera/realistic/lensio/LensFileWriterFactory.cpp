#include "LensFileWriterFactory.h"
#include "crayg/foundation/exceptions/Exceptions.h"
#include "crayg/foundation/logging/Logger.h"
#include "extendedformat/LensFileExtendedFormatWriter.h"
#include "textfile/LensFileTextFileWriter.h"
#include "json/LensFileJsonWriter.h"
#include <filesystem>

namespace crayg {

std::unique_ptr<LensFileWriter> LensFileWriterFactory::createLensFileWriter(const std::string &filePath) {
    std::filesystem::path path(filePath);
    std::string extension = path.extension().string();

    if (extension == ".txt") {
        return std::make_unique<LensFileTextFileWriter>();
    } else if (extension == ".json") {
        return std::make_unique<LensFileJsonWriter>();
    } else if (extension == ".fx") {
        return std::make_unique<LensFileExtendedFormatWriter>();
    } else {
        Logger::error("No LensFileWriter found for extension {}", extension);
        CRAYG_LOG_AND_THROW_RUNTIME_ERROR("No LensFileWriter found for extension {}", extension);
    }
}

std::unique_ptr<LensFileWriter> LensFileWriterFactory::createLensFileWriter(LensFileFormat lensFileFormat) {
    if (lensFileFormat == LensFileFormat::TXT) {
        return std::make_unique<LensFileTextFileWriter>();
    } else if (lensFileFormat == LensFileFormat::JSON) {
        return std::make_unique<LensFileJsonWriter>();
    } else if (lensFileFormat == LensFileFormat::EXTENDED_FORMAT) {
        return std::make_unique<LensFileExtendedFormatWriter>();
    } else {
        Logger::error("No LensFileWriter found for LensFileFormat {}", lensFileFormat);
        CRAYG_LOG_AND_THROW_RUNTIME_ERROR("No LensFileWriter found for LensFileFormat {}", lensFileFormat);
    }
}
}