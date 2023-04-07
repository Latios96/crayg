#include "LensFileWriterFactory.h"
#include "LensFileJsonWriter.h"
#include "LensFileTextFileWriter.h"
#include "Logger.h"
#include <boost/filesystem/path.hpp>

namespace crayg {

std::unique_ptr<LensFileWriter> LensFileWriterFactory::createLensFileWriter(const std::string &filePath) {
    boost::filesystem::path path(filePath);
    std::string extension = path.extension().string();

    if (extension == ".txt") {
        return std::make_unique<LensFileTextFileWriter>();
    } else if (extension == ".json") {
        return std::make_unique<LensFileJsonWriter>();
    } else {
        Logger::error("No LensFileWriter found for extension {}", extension);
        throw std::runtime_error(fmt::format("No LensFileWriter found for extension {}", extension));
    }
}

std::unique_ptr<LensFileWriter> LensFileWriterFactory::createLensFileWriter(LensFileFormat lensFileFormat) {
    if (lensFileFormat == LensFileFormat::TXT) {
        return std::make_unique<LensFileTextFileWriter>();
    } else if (lensFileFormat == LensFileFormat::JSON) {
        return std::make_unique<LensFileJsonWriter>();
    } else {
        Logger::error("No LensFileWriter found for LensFileFormat {}", lensFileFormat);
        throw std::runtime_error(fmt::format("No LensFileWriter found for LensFileFormat {}", lensFileFormat));
    }
}
} // crayg