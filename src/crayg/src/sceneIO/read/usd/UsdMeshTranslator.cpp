//
// Created by Jan on 13.05.2022.
//

#include <pxr/imaging/hd/meshUtil.h>
#include <pxr/imaging/hd/meshTopology.h>
#include "UsdMeshTranslator.h"
#include "UsdUtils.h"
#include "UsdConversions.h"
#include "UsdTranslatorUtils.h"
#include "Logger.h"

namespace crayg {

UsdMeshTranslator::UsdMeshTranslator(const pxr::UsdGeomMesh &usdGeomMesh) : BaseUsdXformableTranslator(usdGeomMesh) {

}

std::shared_ptr<TriangleMesh> crayg::UsdMeshTranslator::translate() {
    auto triangleMesh = BaseUsdXformableTranslator<pxr::UsdGeomMesh, TriangleMesh>::translate();

    pxr::VtVec3iArray triangleIndices;
    computeTriangleIndices(triangleIndices);

    translateFaceIndices(triangleMesh, triangleIndices);
    translatePoints(triangleMesh);

    return triangleMesh;
}
void crayg::UsdMeshTranslator::translateFaceIndices(std::shared_ptr<TriangleMesh> &triangleMesh,
                                                    pxr::VtVec3iArray &triangleIndices) const {
    triangleMesh->faceIndices.reserve(triangleIndices.size());
    for (const auto &faceIndex: triangleIndices) {
        triangleMesh->faceIndices.push_back(faceIndex[0]);
        triangleMesh->faceIndices.push_back(faceIndex[2]);
        triangleMesh->faceIndices.push_back(faceIndex[1]);
    }
}
void crayg::UsdMeshTranslator::translatePoints(std::shared_ptr<TriangleMesh> &triangleMesh) const {
    pxr::VtVec3fArray points;
    usdPrim.GetPointsAttr().Get(&points);
    triangleMesh->points.reserve(points.size());
    for (const auto &point: points) {
        triangleMesh->points.emplace_back(point[0], point[1], -point[2]);
    }
}

void crayg::UsdMeshTranslator::computeTriangleIndices(pxr::VtVec3iArray &triangleIndices) const {
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
std::string UsdMeshTranslator::getTranslatedType() {
    return "mesh";
}

}
