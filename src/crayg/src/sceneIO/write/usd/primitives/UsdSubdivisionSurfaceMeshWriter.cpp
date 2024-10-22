#include "UsdSubdivisionSurfaceMeshWriter.h"
#include "UsdTriangleMeshWriter.h"
#include "sceneIO/usd/UsdUtils.h"
#include <pxr/usd/usdGeom/primvar.h>
#include <pxr/usd/usdGeom/primvarsAPI.h>

namespace crayg {

class _SubdivisionSurfaceTriangleMeshWriter : public UsdTriangleMeshWriter {
  public:
    _SubdivisionSurfaceTriangleMeshWriter(TriangleMesh &craygObject, UsdMaterialWriteCache &usdMaterialWriteCache)
        : UsdTriangleMeshWriter(craygObject, usdMaterialWriteCache) {
    }

  protected:
    std::string getTranslatedType() override {
        return "SubdivisionSurfaceMesh";
    }
};

UsdSubdivisionSurfaceMeshWriter::UsdSubdivisionSurfaceMeshWriter(SubdivisionSurfaceMesh &craygObject,
                                                                 UsdMaterialWriteCache &usdMaterialWriteCache)
    : BaseUsdSceneObjectWriter(craygObject, usdMaterialWriteCache) {
}

pxr::UsdGeomMesh UsdSubdivisionSurfaceMeshWriter::write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) {
    if (this->craygObject.isTesselated()) {
        _SubdivisionSurfaceTriangleMeshWriter subdivisionSurfaceTriangleMeshWriter(this->craygObject.triangleMesh,
                                                                                   usdMaterialWriteCache);
        return subdivisionSurfaceTriangleMeshWriter.write(stage, usdPathFactory);
    }
    auto usdGeomMesh = BaseUsdSceneObjectWriter::write(stage, usdPathFactory);

    writePoints(usdGeomMesh);
    writeFaceVertexIndices(usdGeomMesh);
    writeFaceVertexCounts(usdGeomMesh);
    writeSubdivisionScheme(usdGeomMesh);
    writeUvs(usdGeomMesh);
    writeMaxSubdivision(usdGeomMesh);

    return usdGeomMesh;
}

void UsdSubdivisionSurfaceMeshWriter::writePoints(pxr::UsdGeomMesh usdGeomMesh) const {
    pxr::VtVec3fArray points;
    points.reserve(craygObject.points.size());
    for (auto &i : craygObject.points) {
        points.push_back(UsdConversions::convert(i));
    }
    usdGeomMesh.GetPointsAttr().Set(points);
}

void UsdSubdivisionSurfaceMeshWriter::writeFaceVertexIndices(pxr::UsdGeomMesh usdGeomMesh) const {
    pxr::VtIntArray triangleIndices;
    triangleIndices.reserve(craygObject.faceVertexIndices.size());
    for (auto &indices : craygObject.faceVertexIndices) {
        triangleIndices.push_back(indices);
    }
    usdGeomMesh.GetFaceVertexIndicesAttr().Set(triangleIndices);
}

void UsdSubdivisionSurfaceMeshWriter::writeFaceVertexCounts(pxr::UsdGeomMesh usdGeomMesh) const {
    pxr::VtIntArray faceVertexCounts;
    faceVertexCounts.reserve(craygObject.faceVertexCounts.size());
    for (auto &count : craygObject.faceVertexCounts) {
        faceVertexCounts.push_back(count);
    }
    usdGeomMesh.GetFaceVertexCountsAttr().Set(faceVertexCounts);
}

void UsdSubdivisionSurfaceMeshWriter::writeSubdivisionScheme(pxr::UsdGeomMesh usdGeomMesh) const {
    usdGeomMesh.GetSubdivisionSchemeAttr().Set(pxr::UsdGeomTokens->catmullClark);
}

void UsdSubdivisionSurfaceMeshWriter::writeUvs(pxr::UsdGeomMesh usdGeomMesh) const {
    pxr::VtVec2fArray uvs;
    uvs.reserve(this->craygObject.uvs.size());
    for (auto &uv : this->craygObject.uvs) {
        uvs.push_back(UsdConversions::convert(uv));
    }

    pxr::VtIntArray uvIndices;
    uvIndices.reserve(this->craygObject.uvIndices.size());
    for (auto i : this->craygObject.uvIndices) {
        uvIndices.push_back(i);
    }

    pxr::UsdGeomPrimvarsAPI primvarsApi(usdGeomMesh);
    primvarsApi.CreateIndexedPrimvar(pxr::TfToken("uv"), pxr::SdfValueTypeNames->TexCoord2fArray, uvs, uvIndices,
                                     pxr::UsdGeomTokens->faceVarying);
}

void UsdSubdivisionSurfaceMeshWriter::writeMaxSubdivision(pxr::UsdGeomMesh usdGeomMesh) const {
    UsdUtils::createAndSetAttribute(usdGeomMesh.GetPrim(), "crayg:maxSubdivision", craygObject.maxSubdivision);
}
} // crayg