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
    faceVertexCounts.resize(craygObject->faceCount());
    std::fill(faceVertexCounts.begin(), faceVertexCounts.end(), 3);

    usdGeomMesh.GetFaceVertexCountsAttr().Set(faceVertexCounts);
}
void UsdTriangleMeshWriter::writeFaceVertexIndices(const pxr::UsdGeomMesh &usdGeomMesh) {
    pxr::VtIntArray triangleIndices;
    triangleIndices.reserve(craygObject->faceCount() * 3);
    for (auto &indices: craygObject->faceVertexIndices) {
        triangleIndices.push_back(indices.v0);
        triangleIndices.push_back(indices.v2);
        triangleIndices.push_back(indices.v1);
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