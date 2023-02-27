#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_USDSPHEREREADER_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_USDSPHEREREADER_H_

#include "BaseUsdImageableReader.h"
#include "scene/primitives/Sphere.h"
#include "sceneIO/usd/CraygUsdBase.h"
#include "sceneIO/usd/UsdUtils.h"
#include <pxr/usd/usdGeom/sphere.h>

namespace crayg {

class UsdSphereReader : public BaseUsdImageableReader<pxr::UsdGeomSphere, Sphere> {
  public:
    UsdSphereReader(const pxr::UsdGeomSphere &usdPrim, UsdMaterialReadCache &usdMaterialTranslationCache);
    std::shared_ptr<Sphere> read() override;

  protected:
    std::string getTranslatedType() override;
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_USDSPHEREREADER_H_
