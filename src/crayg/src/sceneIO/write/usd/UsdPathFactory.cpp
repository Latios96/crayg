#include "UsdPathFactory.h"
#include <fmt/format.h>

namespace crayg {
pxr::SdfPath UsdPathFactory::getPathForName(const std::string &name, const std::string &type) {
    if (!name.empty()) {
        return nameToPath(name);
    }
    int counter = typeCounter[type]++;
    return nameToPath(fmt::format("{}{}", type, counter));
}

pxr::SdfPath UsdPathFactory::nameToPath(const std::string &name) {
    if (name[0] == '/') {
        return pxr::SdfPath(name);
    }
    return pxr::SdfPath("/" + name);
}
}