#ifndef CRAYG_SRC_CRAYGUSD_SRC_USDMESHTRANSLATOR_H_
#define CRAYG_SRC_CRAYGUSD_SRC_USDMESHTRANSLATOR_H_

#include "scene/primitives/trianglemesh/TriangleMesh.h"
#include "sceneIO/read/usd/base/BaseUsdImageableReader.h"
#include "sceneIO/usd/CraygUsdBase.h"
#include <pxr/imaging/hd/meshUtil.h>
#include <pxr/usd/usdGeom/mesh.h>

namespace crayg {

class UsdMeshReader : public BaseUsdImageableReader<pxr::UsdGeomMesh, TriangleMesh> {
  public:
    UsdMeshReader(const pxr::UsdGeomMesh &usdPrim, UsdMaterialReadCache &usdMaterialTranslationCache);
    std::shared_ptr<TriangleMesh> read() override;

  protected:
    std::string getTranslatedType() override;

  private:
    void computeTriangleIndices(pxr::VtVec3iArray &triangleIndices, pxr::HdMeshUtil &meshUtil) const;
    void translatePoints(std::shared_ptr<TriangleMesh> &triangleMesh) const;
    void translateFaceIndices(std::shared_ptr<TriangleMesh> &triangleMesh, pxr::VtVec3iArray &triangleIndices) const;
    pxr::HdMeshTopology *getMeshUtil() const;
    void translateNormals(std::shared_ptr<TriangleMesh> &sharedPtr, pxr::HdMeshUtil &util);
    void translateUvs(std::shared_ptr<TriangleMesh> &sharedPtr, pxr::HdMeshUtil &util);
    void translateFaceVaryingNormals(std::shared_ptr<TriangleMesh> &triangleMesh,
                                     const pxr::HdMeshUtil &meshUtil) const;
    void translateVertexNormals(std::shared_ptr<TriangleMesh> &triangleMesh, const pxr::HdMeshUtil &meshUtil) const;
    pxr::VtValue &computeTriangulatedFaceVaryingNormals(const pxr::HdMeshUtil &meshUtil,
                                                        pxr::VtValue &triangulated) const;
    bool normalsAreAuthored() const;

    void translateFaceVaryingUvs(std::shared_ptr<TriangleMesh> &triangleMesh, const pxr::HdMeshUtil &meshUtil,
                                 pxr::UsdGeomPrimvar &uvsPrimvar) const;
    pxr::VtValue &computeTriangulatedFaceVaryingUvs(const pxr::HdMeshUtil &meshUtil, pxr::VtValue &triangulated,
                                                    pxr::UsdGeomPrimvar &uvsPrimvar) const;
    std::optional<pxr::UsdGeomPrimvar> getAuthoredUvPrimVar() const;
};

}

#endif // CRAYG_SRC_CRAYGUSD_SRC_USDMESHTRANSLATOR_H_
