#include "LensFileReader.h"
#include <boost/filesystem.hpp>

namespace crayg {

LensFileReader::LensFileReader(const std::string &filePath) : filePath(filePath) {
}

CameraLens LensFileReader::readFile() {
    if (!boost::filesystem::exists(filePath)) {
        throw std::runtime_error(fmt::format("Lens file {} does not exist.", filePath));
    }

    std::ifstream t(filePath);
    std::stringstream buffer;
    buffer << t.rdbuf();
    return readFileContent(buffer.str());
}

}