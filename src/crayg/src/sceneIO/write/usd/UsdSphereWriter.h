#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDSPHEREWRITER_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDSPHEREWRITER_H_

#include "BaseUsdSceneObjectWriter.h"
#include <pxr/usd/usdGeom/sphere.h>
#include "scene/primitives/Sphere.h"

namespace crayg {

class UsdSphereWriter : public BaseUsdSceneObjectWriter<pxr::UsdGeomSphere, Sphere> {
 public:
    UsdSphereWriter(const std::shared_ptr<Sphere> &craygObject, UsdMaterialWriteCache &usdMaterialWriteCache);

    pxr::UsdGeomSphere write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) override;

};

} // crayg

#endif //CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDSPHEREWRITER_H_
