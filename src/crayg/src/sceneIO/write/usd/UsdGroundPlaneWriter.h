#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDGROUNDPLANEWRITER_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDGROUNDPLANEWRITER_H_

#include "BaseUsdSceneObjectWriter.h"
#include "UsdTriangleMeshWriter.h"
#include "scene/primitives/GroundPlane.h"
#include <pxr/usd/usdGeom/mesh.h>

namespace crayg {

class UsdGroundPlaneWriter : public BaseUsdSceneObjectWriter<pxr::UsdGeomMesh, GroundPlane> {
  public:
    UsdGroundPlaneWriter(GroundPlane &craygObject, UsdMaterialWriteCache &usdMaterialWriteCache);

    pxr::UsdGeomMesh write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) override;

  protected:
    std::string getTranslatedType() override;
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDGROUNDPLANEWRITER_H_
