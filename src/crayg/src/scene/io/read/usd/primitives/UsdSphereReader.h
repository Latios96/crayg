#pragma once

#include "scene/io/read/usd/base/BaseUsdImageableReader.h"
#include "scene/io/usd/UsdUtils.h"
#include "scene/primitives/Sphere.h"
#include <pxr/usd/usdGeom/sphere.h>

namespace crayg {

class UsdSphereReader : public BaseUsdImageableReader<pxr::UsdGeomSphere, Sphere> {
  public:
    UsdSphereReader(const pxr::UsdGeomSphere &usdPrim, UsdMaterialReadCache &usdMaterialTranslationCache);
    std::shared_ptr<Sphere> read() override;

  protected:
    std::string getTranslatedType() override;
};

}
