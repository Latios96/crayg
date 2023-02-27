#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDSUBDIVISIONSURFACEMESHWRITER_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDSUBDIVISIONSURFACEMESHWRITER_H_

#include "BaseUsdSceneObjectWriter.h"
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
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDSUBDIVISIONSURFACEMESHWRITER_H_
