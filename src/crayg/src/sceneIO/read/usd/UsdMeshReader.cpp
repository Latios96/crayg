//
// Created by Jan on 13.05.2022.
//

#include <pxr/imaging/hd/meshUtil.h>
#include <pxr/imaging/hd/meshTopology.h>
#include "UsdMeshReader.h"
#include "sceneIO/usd/UsdUtils.h"
#include "sceneIO/usd/UsdConversions.h"

namespace crayg {

UsdMeshReader::UsdMeshReader(const pxr::UsdGeomMesh &usdPrim,
                             UsdMaterialReadCache &usdMaterialTranslationCache)
    : BaseUsdImageableReader(usdPrim, usdMaterialTranslationCache) {}

std::shared_ptr<TriangleMesh> crayg::UsdMeshReader::read() {
    auto triangleMesh = BaseUsdImageableReader<pxr::UsdGeomMesh, TriangleMesh>::read();

    pxr::VtVec3iArray triangleIndices;
    computeTriangleIndices(triangleIndices);

    translateFaceIndices(triangleMesh, triangleIndices);
    translatePoints(triangleMesh);

    return triangleMesh;
}
void crayg::UsdMeshReader::translateFaceIndices(std::shared_ptr<TriangleMesh> &triangleMesh,
                                                pxr::VtVec3iArray &triangleIndices) const {
    triangleMesh->faceIndices.reserve(triangleIndices.size());
    for (const auto &faceIndex: triangleIndices) {
        triangleMesh->faceIndices.push_back(faceIndex[0]);
        triangleMesh->faceIndices.push_back(faceIndex[2]);
        triangleMesh->faceIndices.push_back(faceIndex[1]);
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

void crayg::UsdMeshReader::computeTriangleIndices(pxr::VtVec3iArray &triangleIndices) const {
    auto scheme = UsdUtils::getAttributeValueAs<pxr::TfToken>(usdPrim.GetSubdivisionSchemeAttr());
    auto orientation = UsdUtils::getAttributeValueAs<pxr::TfToken>(usdPrim.GetOrientationAttr());

    pxr::VtIntArray faceVertexCounts, faceVertexIndices, holeIndices;
    usdPrim.GetFaceVertexCountsAttr().Get(&faceVertexCounts);
    usdPrim.GetFaceVertexIndicesAttr().Get(&faceVertexIndices);
    usdPrim.GetHoleIndicesAttr().Get(&holeIndices);

    pxr::HdMeshTopology topology(scheme, orientation, faceVertexCounts, faceVertexIndices, holeIndices);
    pxr::HdMeshUtil meshUtil(&topology, usdPrim.GetPath());

    pxr::VtIntArray primitiveParams;
    meshUtil.ComputeTriangleIndices(&triangleIndices, &primitiveParams);
}
std::string UsdMeshReader::getTranslatedType() {
    return "mesh";
}

}

