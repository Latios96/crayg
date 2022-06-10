//
// Created by Jan on 05.06.2022.
//

#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDGROUNDPLANEWRITER_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDGROUNDPLANEWRITER_H_

#include "BaseUsdSceneObjectWriter.h"
#include <pxr/usd/usdGeom/mesh.h>
#include "scene/GroundPlane.h"
#include "UsdTriangleMeshWriter.h"

namespace crayg {

class _SpecialUsdTriangleMeshWriter : public UsdTriangleMeshWriter {
 public:
    _SpecialUsdTriangleMeshWriter(const std::shared_ptr<TriangleMesh> &craygObject,
                                  UsdMaterialWriteCache &usdMaterialWriteCache);
 protected:
    std::string getTranslatedType() override;
};

class UsdGroundPlaneWriter : public BaseUsdSceneObjectWriter<pxr::UsdGeomMesh, GroundPlane> {
 public:
    UsdGroundPlaneWriter(const std::shared_ptr<GroundPlane> &craygObject, UsdMaterialWriteCache &usdMaterialWriteCache);

    pxr::UsdGeomMesh write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) override;
 protected:
    std::string getTranslatedType() override;
};

} // crayg

#endif //CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDGROUNDPLANEWRITER_H_