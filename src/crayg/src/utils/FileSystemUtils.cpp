#include "FileSystemUtils.h"
#include <boost/filesystem/path.hpp>

namespace crayg {

std::string FileSystemUtils::swapFileExtension(const std::string &path, const std::string &newExtension) {
    auto boostPath = boost::filesystem::path(path);
    return boostPath.replace_extension(newExtension).string();
}

} // crayg