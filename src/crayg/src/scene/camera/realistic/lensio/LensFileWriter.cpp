#include "LensFileWriter.h"
#include "utils/Exceptions.h"
#include <filesystem>
#include <sstream>

namespace crayg {

void LensFileWriter::writeFile(const std::string &filePath, const crayg::CameraLens &cameraLens) {
    const auto targetDirectory = std::filesystem::absolute(filePath).parent_path();
    if (!std::filesystem::exists(targetDirectory)) {
        CRAYG_LOG_AND_THROW_RUNTIME_ERROR("Lens file target directory '{}' does not exist.", targetDirectory.string());
    }

    std::ofstream o(filePath);
    o << writeFileContent(cameraLens);
    o.close();
}

} // crayg