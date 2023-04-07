#include "LensFileWriter.h"
#include <boost/filesystem.hpp>
#include <sstream>

namespace crayg {

void LensFileWriter::writeFile(const std::string &filePath, const crayg::CameraLens &cameraLens) {
    const auto targetDirectory = boost::filesystem::path(filePath).parent_path();
    if (!boost::filesystem::exists(targetDirectory)) {
        throw std::runtime_error(
            fmt::format("Lens file target directory {} does not exist.", targetDirectory.string()));
    }

    std::ofstream o(filePath);
    o << writeFileContent(cameraLens);
    o.close();
}

} // crayg