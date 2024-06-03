#pragma once

#include "UsdTriangleMeshWriter.h"
#include "scene/primitives/GroundPlane.h"
#include "sceneIO/write/usd/base/BaseUsdSceneObjectWriter.h"
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
