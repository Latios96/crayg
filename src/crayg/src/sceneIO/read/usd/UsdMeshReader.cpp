//
// Created by Jan on 13.05.2022.
//

#include <pxr/imaging/hd/meshTopology.h>
#include <pxr/imaging/hd/vtBufferSource.h>
#include "UsdMeshReader.h"
#include "sceneIO/usd/UsdUtils.h"
#include "sceneIO/usd/UsdConversions.h"
#include "scene/trianglemesh/primvars/TriangleMeshPerVertexPrimVar.h"

namespace crayg {

UsdMeshReader::UsdMeshReader(const pxr::UsdGeomMesh &usdPrim,
                             UsdMaterialReadCache &usdMaterialTranslationCache)
    : BaseUsdImageableReader(usdPrim, usdMaterialTranslationCache) {}

std::shared_ptr<TriangleMesh> crayg::UsdMeshReader::read() {
    auto triangleMesh = BaseUsdImageableReader<pxr::UsdGeomMesh, TriangleMesh>::read();

    auto topology = std::unique_ptr<pxr::HdMeshTopology>(getMeshUtil());
    pxr::HdMeshUtil meshUtil(topology.get(), usdPrim.GetPath());

    pxr::VtVec3iArray triangleIndices;
    computeTriangleIndices(triangleIndices, meshUtil);

    translateFaceIndices(triangleMesh, triangleIndices);
    translatePoints(triangleMesh);
    translateNormals(triangleMesh, meshUtil);

    return triangleMesh;
}
void crayg::UsdMeshReader::translateFaceIndices(std::shared_ptr<TriangleMesh> &triangleMesh,
                                                pxr::VtVec3iArray &triangleIndices) const {
    triangleMesh->faceVertexIndices.reserve(triangleIndices.size());
    for (const auto &faceIndex: triangleIndices) {
        triangleMesh->faceVertexIndices.emplace_back(faceIndex[0], faceIndex[2], faceIndex[1]);
    }
}
void crayg::UsdMeshReader::translatePoints(std::shared_ptr<TriangleMesh> &triangleMesh) const {
    pxr::VtVec3fArray points;
    usdPrim.GetPointsAttr().Get(&points);
    triangleMesh->points.reserve(points.size());
    for (const auto &point: points) {
        triangleMesh->points.emplace_back(point[0], point[1], -point[2]);
    }
}

void crayg::UsdMeshReader::computeTriangleIndices(pxr::VtVec3iArray &triangleIndices, pxr::HdMeshUtil &meshUtil) const {
    pxr::VtIntArray primitiveParams;
    meshUtil.ComputeTriangleIndices(&triangleIndices, &primitiveParams);
}

pxr::HdMeshTopology *crayg::UsdMeshReader::getMeshUtil() const {
    auto scheme = UsdUtils::getAttributeValueAs<pxr::TfToken>(usdPrim.GetSubdivisionSchemeAttr());
    auto orientation = UsdUtils::getAttributeValueAs<pxr::TfToken>(usdPrim.GetOrientationAttr());

    pxr::VtIntArray faceVertexCounts, faceVertexIndices, holeIndices;
    usdPrim.GetFaceVertexCountsAttr().Get(&faceVertexCounts);
    usdPrim.GetFaceVertexIndicesAttr().Get(&faceVertexIndices);
    usdPrim.GetHoleIndicesAttr().Get(&holeIndices);

    return new pxr::HdMeshTopology(scheme, orientation, faceVertexCounts, faceVertexIndices, holeIndices);
}

std::string UsdMeshReader::getTranslatedType() {
    return "mesh";
}

void UsdMeshReader::translateNormals(std::shared_ptr<TriangleMesh> &triangleMesh, pxr::HdMeshUtil &meshUtil) {
    const pxr::TfToken normalsInterpolation = usdPrim.GetNormalsInterpolation();
    if (normalsInterpolation == pxr::UsdGeomTokens->faceVarying) {
        translateFaceVaryingNormals(triangleMesh, meshUtil);
    } else {
        Logger::warning(R"(Normals interpolation "{}" of mesh {} is not supported)",
                        normalsInterpolation,
                        usdPrim.GetPath());
    }
}
void UsdMeshReader::translateFaceVaryingNormals(std::shared_ptr<TriangleMesh> &triangleMesh,
                                                const pxr::HdMeshUtil &meshUtil) const {
    pxr::VtValue triangulated;
    triangulated = computeTriangulatedFaceVaryingNormals(meshUtil, triangulated);

    auto *primVar = triangleMesh->addNormalsPrimVar<TriangleMeshPerVertexPrimVar<Vector3f>>();

    auto data = static_cast<const pxr::GfVec3f *>(pxr::HdGetValueData(triangulated));
    for (auto id: triangleMesh->faceIds()) {
        primVar->write(id,
                       UsdConversions::convert(data[id * 3]),
                       UsdConversions::convert(data[id * 3 + 2]),
                       UsdConversions::convert(data[id * 3 + 1]));
    }
}
pxr::VtValue &UsdMeshReader::computeTriangulatedFaceVaryingNormals(const pxr::HdMeshUtil &meshUtil,
                                                                   pxr::VtValue &triangulated) const {
    pxr::VtVec3fArray normals;
    usdPrim.GetNormalsAttr().Get(&normals);
    meshUtil.ComputeTriangulatedFaceVaryingPrimvar(normals.data(),
                                                   normals.size(),
                                                   pxr::HdTypeFloatVec3,
                                                   &triangulated);
    return triangulated;
}

}

