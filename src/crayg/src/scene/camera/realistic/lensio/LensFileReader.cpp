#include "LensFileReader.h"
#include "crayg/foundation/exceptions/Exceptions.h"
#include "crayg/foundation/filesystem/FileAsString.h"
#include <filesystem>
#include <sstream>

namespace crayg {

CameraLens LensFileReader::readFile(const std::string &filePath) {
    if (!std::filesystem::exists(filePath)) {
        CRAYG_LOG_AND_THROW_RUNTIME_ERROR("Lens file {} does not exist.", filePath);
    }

    const std::string buffer = FileAsString::readFileAsString(filePath);
    return readFileContent(buffer);
}

}