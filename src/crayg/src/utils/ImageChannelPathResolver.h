#ifndef CRAYG_SRC_CRAYG_SRC_UTILS_IMAGECHANNELPATHRESOLVER_H_
#define CRAYG_SRC_CRAYG_SRC_UTILS_IMAGECHANNELPATHRESOLVER_H_

#include <string>

namespace crayg {

class ImageChannelPathResolver {
 public:
    std::string resolve(const std::string &path, const std::string &channelName);
};

} // crayg

#endif //CRAYG_SRC_CRAYG_SRC_UTILS_IMAGECHANNELPATHRESOLVER_H_
