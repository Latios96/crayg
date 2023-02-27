#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDPATHFACTORY_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDPATHFACTORY_H_

#include <pxr/usd/sdf/path.h>
#include <string>

namespace crayg {

class UsdPathFactory {
  public:
    pxr::SdfPath getPathForName(const std::string &name, const std::string &type);

  private:
    std::unordered_map<std::string, int> typeCounter;
    pxr::SdfPath nameToPath(const std::string &name);
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDPATHFACTORY_H_
