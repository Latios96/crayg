#include "FileSystemUtils.h"
#include <boost/filesystem/path.hpp>
#include <fstream>
#include <sstream>

namespace crayg {

std::string FileSystemUtils::swapFileExtension(const std::string &path, const std::string &newExtension) {
    auto boostPath = boost::filesystem::path(path);
    return boostPath.replace_extension(newExtension).string();
}

std::string FileSystemUtils::readFileAsString(const std::string &path) {
    std::ifstream inputStream(path);
    std::stringstream buffer;
    buffer << inputStream.rdbuf();
    return buffer.str();
}

} // crayg