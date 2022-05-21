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

crayg::UsdMeshTranslator::UsdMeshTranslator(const pxr::UsdGeomMesh &usdGeomMesh) : usdGeomMesh(usdGeomMesh) {};

std::shared_ptr<TriangleMesh> crayg::UsdMeshTranslator::translate() {
    Logger::debug("Translating mesh {}", usdGeomMesh.GetPath().GetString());

    auto triangleMesh = std::make_shared<crayg::TriangleMesh>();
    UsdTranslatorUtils::translateTransform(*triangleMesh, usdGeomMesh);

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
    usdGeomMesh.GetPointsAttr().Get(&points);
    triangleMesh->points.reserve(points.size());
    for (const auto &point: points) {
        triangleMesh->points.emplace_back(point[0], point[1], -point[2]);
    }
}

void crayg::UsdMeshTranslator::computeTriangleIndices(pxr::VtVec3iArray &triangleIndices) const {
    auto scheme = UsdUtils::getAttributeValueAs<pxr::TfToken>(usdGeomMesh.GetSubdivisionSchemeAttr());
    auto orientation = UsdUtils::getAttributeValueAs<pxr::TfToken>(usdGeomMesh.GetOrientationAttr());

    pxr::VtIntArray faceVertexCounts, faceVertexIndices, holeIndices;
    usdGeomMesh.GetFaceVertexCountsAttr().Get(&faceVertexCounts);
    usdGeomMesh.GetFaceVertexIndicesAttr().Get(&faceVertexIndices);
    usdGeomMesh.GetHoleIndicesAttr().Get(&holeIndices);

    pxr::HdMeshTopology topology(scheme, orientation, faceVertexCounts, faceVertexIndices, holeIndices);
    pxr::HdMeshUtil meshUtil(&topology, usdGeomMesh.GetPath());

    pxr::VtIntArray primitiveParams;
    meshUtil.ComputeTriangleIndices(&triangleIndices, &primitiveParams);
}

}
