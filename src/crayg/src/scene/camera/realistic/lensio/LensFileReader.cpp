#include "LensFileReader.h"
#include "utils/Exceptions.h"
#include "utils/FileSystemUtils.h"
#include <filesystem>
#include <sstream>

namespace crayg {

CameraLens LensFileReader::readFile(const std::string &filePath) {
    if (!std::filesystem::exists(filePath)) {
        CRAYG_LOG_AND_THROW_RUNTIME_ERROR("Lens file {} does not exist.", filePath);
    }

    const std::string buffer = FileSystemUtils::readFileAsString(filePath);
    return readFileContent(buffer);
}

}