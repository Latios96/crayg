#ifndef CRAYG_SRC_CRAYG_SRC_UTILS_FILESYSTEMUTILS_H_
#define CRAYG_SRC_CRAYG_SRC_UTILS_FILESYSTEMUTILS_H_

#include <string>

namespace crayg {

class FileSystemUtils {
  public:
    static std::string swapFileExtension(const std::string &path, const std::string &newExtension);
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_UTILS_FILESYSTEMUTILS_H_
