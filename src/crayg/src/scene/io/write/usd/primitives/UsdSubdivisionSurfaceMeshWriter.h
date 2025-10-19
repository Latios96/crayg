#pragma once

#include "scene/io/write/usd/UsdPathFactory.h"
#include "scene/io/write/usd/base/BaseUsdSceneObjectWriter.h"
#include "scene/io/write/usd/shadingnetworks/caches/UsdMaterialWriteCache.h"
#include "scene/primitives/subdivisionsurfacemesh/SubdivisionSurfaceMesh.h"
#include <pxr/usd/usdGeom/mesh.h>

namespace crayg {

class UsdSubdivisionSurfaceMeshWriter : public BaseUsdSceneObjectWriter<pxr::UsdGeomMesh, SubdivisionSurfaceMesh> {
  public:
    UsdSubdivisionSurfaceMeshWriter(SubdivisionSurfaceMesh &craygObject, UsdMaterialWriteCache &usdMaterialWriteCache);

    pxr::UsdGeomMesh write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) override;

  protected:
    void writePoints(pxr::UsdGeomMesh usdGeomMesh) const;
    void writeFaceVertexIndices(pxr::UsdGeomMesh usdGeomMesh) const;
    void writeFaceVertexCounts(pxr::UsdGeomMesh usdGeomMesh) const;
    void writeSubdivisionScheme(pxr::UsdGeomMesh usdGeomMesh) const;
    void writeUvs(pxr::UsdGeomMesh usdGeomMesh) const;
    void writeMaxSubdivision(pxr::UsdGeomMesh usdGeomMesh) const;
};

}
