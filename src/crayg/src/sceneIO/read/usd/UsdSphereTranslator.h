//
// Created by Jan on 21.05.2022.
//

#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_USDSPHERETRANSLATOR_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_USDSPHERETRANSLATOR_H_

#include "CraygUsdBase.h"
#include "BaseUsdImageableTranslator.h"
#include "scene/Sphere.h"
#include "UsdUtils.h"
#include <pxr/usd/usdGeom/sphere.h>

namespace crayg {

class UsdSphereTranslator : public BaseUsdImageableTranslator<pxr::UsdGeomSphere, Sphere> {
 public:
    UsdSphereTranslator(const pxr::UsdGeomSphere &usdPrim, UsdMaterialTranslationCache &usdMaterialTranslationCache);
    std::shared_ptr<Sphere> translate() override;
 protected:
    std::string getTranslatedType() override;
};

} // crayg

#endif //CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_USDSPHERETRANSLATOR_H_
