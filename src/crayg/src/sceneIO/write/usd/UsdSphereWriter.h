//
// Created by Jan on 03.06.2022.
//

#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDSPHEREWRITER_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDSPHEREWRITER_H_

#include "BaseUsdTransformableWriter.h"
#include <pxr/usd/usdGeom/sphere.h>
#include "scene/Sphere.h"

namespace crayg {

class UsdSphereWriter : public BaseUsdTransformableWriter<pxr::UsdGeomSphere, Sphere> {
 public:
    UsdSphereWriter(const std::shared_ptr<Sphere> &craygObject);

    pxr::UsdGeomSphere write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) override;

 protected:
    std::string getTranslatedType() override;
};

} // crayg

#endif //CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDSPHEREWRITER_H_
