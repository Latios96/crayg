#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDTRIANGLEMESHWRITER_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDTRIANGLEMESHWRITER_H_

#include "BaseUsdSceneObjectWriter.h"
#include <pxr/usd/usdGeom/mesh.h>
#include "scene/primitives/trianglemesh/TriangleMesh.h"

namespace crayg {

class UsdTriangleMeshWriter : public BaseUsdSceneObjectWriter<pxr::UsdGeomMesh, TriangleMesh> {
 public:
    UsdTriangleMeshWriter(TriangleMesh &craygObject,
                          UsdMaterialWriteCache &usdMaterialWriteCache);
    pxr::UsdGeomMesh write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) override;

 private:
    void writePoints(const pxr::UsdGeomMesh &usdGeomMesh);
    void writeFaceVertexIndices(const pxr::UsdGeomMesh &usdGeomMesh);
    void writeFaceVertexCounts(const pxr::UsdGeomMesh &usdGeomMesh) const;
    void writeSubdivisionScheme(const pxr::UsdGeomMesh &usdGeomMesh) const;
};

} // crayg

#endif //CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDTRIANGLEMESHWRITER_H_
