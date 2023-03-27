#include "UsdTriangleMeshWriter.h"
#include "scene/primitives/trianglemesh/primvars/TriangleMeshPerPointPrimVar.h"
#include "scene/primitives/trianglemesh/primvars/TriangleMeshPerVertexPrimVar.h"
#include "sceneIO/usd/UsdConversions.h"

namespace crayg {

UsdTriangleMeshWriter::UsdTriangleMeshWriter(TriangleMesh &craygObject, UsdMaterialWriteCache &usdMaterialWriteCache)
    : BaseUsdSceneObjectWriter(craygObject, usdMaterialWriteCache) {
}

pxr::UsdGeomMesh UsdTriangleMeshWriter::write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) {
    auto usdGeomMesh = BaseUsdSceneObjectWriter::write(stage, usdPathFactory);

    writePoints(usdGeomMesh);
    writeFaceVertexIndices(usdGeomMesh);
    writeFaceVertexCounts(usdGeomMesh);
    writeNormals(usdGeomMesh);
    writeSubdivisionScheme(usdGeomMesh);

    return usdGeomMesh;
}

void UsdTriangleMeshWriter::writeFaceVertexCounts(const pxr::UsdGeomMesh &usdGeomMesh) const {
    pxr::VtIntArray faceVertexCounts;
    faceVertexCounts.resize(craygObject.faceCount());
    std::fill(faceVertexCounts.begin(), faceVertexCounts.end(), 3);

    usdGeomMesh.GetFaceVertexCountsAttr().Set(faceVertexCounts);
}

void UsdTriangleMeshWriter::writeFaceVertexIndices(const pxr::UsdGeomMesh &usdGeomMesh) {
    pxr::VtIntArray triangleIndices;
    triangleIndices.reserve(craygObject.faceCount() * 3);
    for (auto &indices : craygObject.faceVertexIndices) {
        triangleIndices.push_back(indices.v0);
        triangleIndices.push_back(indices.v2);
        triangleIndices.push_back(indices.v1);
    }
    usdGeomMesh.GetFaceVertexIndicesAttr().Set(triangleIndices);
}

void UsdTriangleMeshWriter::writePoints(const pxr::UsdGeomMesh &usdGeomMesh) {
    pxr::VtVec3fArray points;
    points.reserve(craygObject.points.size());
    Transform inverse = Transform(craygObject.getTransform().matrix.invert());
    for (auto &i : craygObject.points) {
        Vector3f point = inverse.applyForPoint(i);
        points.push_back(UsdConversions::convert(point));
    }
    usdGeomMesh.GetPointsAttr().Set(points);
}

void UsdTriangleMeshWriter::writeNormals(pxr::UsdGeomMesh &usdGeomMesh) const {
    if (!this->craygObject.normalsPrimVar) {
        return;
    }
    if (this->craygObject.normalsPrimVar->getType() == PER_POINT) {
        writePerPointNormals(usdGeomMesh);
    } else if (this->craygObject.normalsPrimVar->getType() == PER_VERTEX) {
        writePerVertexNormals(usdGeomMesh);
    } else {
        Logger::warning(R"(Normals interpolation "{}" of mesh {} is not supported)",
                        this->craygObject.normalsPrimVar->getType(), this->craygObject.getName());
    }
}

void UsdTriangleMeshWriter::writePerPointNormals(pxr::UsdGeomMesh &mesh) const {
    pxr::VtVec3fArray normals;
    normals.reserve(this->craygObject.points.size());
    auto normalsPrimVar = this->craygObject.getNormalsPrimVarAs<TriangleMeshPerPointPrimVar<Vector3f>>();
    for (int i = 0; i < craygObject.points.size(); i++) {
        normals.push_back(UsdConversions::convert(normalsPrimVar->read(i)));
    }

    mesh.GetNormalsAttr().Set(normals);
    mesh.SetNormalsInterpolation(pxr::UsdGeomTokens->vertex);
}

void UsdTriangleMeshWriter::writePerVertexNormals(pxr::UsdGeomMesh &mesh) const {
    pxr::VtVec3fArray normals;
    normals.reserve(this->craygObject.faceCount() * 3);
    auto normalsPrimVar = this->craygObject.getNormalsPrimVarAs<TriangleMeshPerVertexPrimVar<Vector3f>>();
    for (auto faceId : this->craygObject.faceIds()) {
        auto vertexData = normalsPrimVar->read(faceId);
        normals.push_back(UsdConversions::convert(vertexData.v0));
        normals.push_back(UsdConversions::convert(vertexData.v2));
        normals.push_back(UsdConversions::convert(vertexData.v1));
    }

    mesh.GetNormalsAttr().Set(normals);
    mesh.SetNormalsInterpolation(pxr::UsdGeomTokens->faceVarying);
}

void UsdTriangleMeshWriter::writeSubdivisionScheme(const pxr::UsdGeomMesh &usdGeomMesh) const {
    usdGeomMesh.GetSubdivisionSchemeAttr().Set(pxr::UsdGeomTokens->none);
}

} // crayg