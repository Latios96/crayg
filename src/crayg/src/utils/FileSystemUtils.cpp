#include <boost/filesystem/path.hpp>
#include "FileSystemUtils.h"

namespace crayg {

std::string FileSystemUtils::swapFileExtension(const std::string &path, const std::string &newExtension) {
    auto boostPath = boost::filesystem::path(path);
    return boostPath.replace_extension(newExtension).string();
}

} // crayg