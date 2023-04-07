#include "LensFileReader.h"
#include <boost/filesystem.hpp>
#include <sstream>

namespace crayg {

CameraLens LensFileReader::readFile(const std::string &filePath) {
    if (!boost::filesystem::exists(filePath)) {
        throw std::runtime_error(fmt::format("Lens file {} does not exist.", filePath));
    }

    std::ifstream t(filePath);
    std::stringstream buffer;
    buffer << t.rdbuf();
    return readFileContent(buffer.str());
}

}