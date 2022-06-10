//
// Created by Jan on 05.06.2022.
//

#include "UsdTriangleMeshWriter.h"

namespace crayg {

UsdTriangleMeshWriter::UsdTriangleMeshWriter(const std::shared_ptr<TriangleMesh> &craygObject,
                                             UsdMaterialWriteCache &usdMaterialWriteCache) : BaseUsdSceneObjectWriter(
    craygObject,
    usdMaterialWriteCache) {}

pxr::UsdGeomMesh UsdTriangleMeshWriter::write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) {
    auto usdGeomMesh = BaseUsdSceneObjectWriter::write(stage, usdPathFactory);

    writePoints(usdGeomMesh);
    writeFaceVertexIndices(usdGeomMesh);
    writeFaceVertexCounts(usdGeomMesh);

    return usdGeomMesh;
}
void UsdTriangleMeshWriter::writeFaceVertexCounts(const pxr::UsdGeomMesh &usdGeomMesh) const {
    pxr::VtIntArray faceVertexCounts;
    faceVertexCounts.reserve(craygObject->faceIndices.size() / 3);
    for (int i = 0; i < craygObject->faceIndices.size(); i += 3) {
        faceVertexCounts.push_back(3);
    }
    usdGeomMesh.GetFaceVertexCountsAttr().Set(faceVertexCounts);
}
void UsdTriangleMeshWriter::writeFaceVertexIndices(const pxr::UsdGeomMesh &usdGeomMesh) {
    pxr::VtIntArray triangleIndices;
    triangleIndices.reserve(craygObject->faceIndices.size());
    for (int i = 0; i < craygObject->faceIndices.size(); i += 3) {
        triangleIndices.push_back(craygObject->faceIndices[i]);
        triangleIndices.push_back(craygObject->faceIndices[i + 2]);
        triangleIndices.push_back(craygObject->faceIndices[i + 1]);
    }
    usdGeomMesh.GetFaceVertexIndicesAttr().Set(triangleIndices);
}
void UsdTriangleMeshWriter::writePoints(const pxr::UsdGeomMesh &usdGeomMesh) {
    pxr::VtVec3fArray points;
    points.reserve(craygObject->points.size());
    Transform inverse = Transform(craygObject->getTransform().matrix.invert());
    for (auto &i: craygObject->points) {
        Vector3f point = inverse.apply(i);
        points.push_back(UsdConversions::convert(point));
    }
    usdGeomMesh.GetPointsAttr().Set(points);
}
} // crayg