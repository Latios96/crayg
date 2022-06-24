#ifndef CRAYG_SRC_CRAYG_SRC_IMAGEPATHRESOLVER_H_
#define CRAYG_SRC_CRAYG_SRC_IMAGEPATHRESOLVER_H_

#include <string>

namespace crayg {

class ImagePathResolver {
 public:
    std::string resolve(const std::string &pathTemplate) const;
    int parseImageNumber(const std::string path) const;
    bool matchesTemplate(const std::string &pathTemplate, const std::string path) const;
};

}

#endif //CRAYG_SRC_CRAYG_SRC_IMAGEPATHRESOLVER_H_
