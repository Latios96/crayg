#include "SubdivisionSurfaceMesh.h"
#include "FanTriangulator.h"
#include "OpenSubdivRefiner.h"
#include "scene/primitives/trianglemesh/primvars/TriangleMeshPerPointPrimVar.h"
#include "scene/primitives/trianglemesh/primvars/TriangleMeshPerVertexPrimVar.h"
#include "utils/tracing/CraygTracing.h"

namespace crayg {

Vector3f SubdivisionSurfaceMesh::getNormal(Vector3f point) {
    verifyIsTessellated();
    return triangleMesh.getNormal(point);
}

Imageable::Intersection SubdivisionSurfaceMesh::intersect(Ray ray) {
    verifyIsTessellated();
    return triangleMesh.intersect(ray);
}

bool SubdivisionSurfaceMesh::isIntersecting(Ray ray) {
    verifyIsTessellated();
    return triangleMesh.isIntersecting(ray);
}

BoundingBox SubdivisionSurfaceMesh::getBounds() const {
    verifyIsTessellated();
    return triangleMesh.getBounds();
}

std::string SubdivisionSurfaceMesh::getType() {
    return "SubdivisionSurfaceMesh";
}

void SubdivisionSurfaceMesh::verifyIsTessellated() const {
    if (!isTessellated) {
        CRAYG_LOG_AND_THROW(std::runtime_error("SubdivisionSurfaceMesh instance was not tesselated!"));
    }
}

void SubdivisionSurfaceMesh::getPrimitives(std::vector<Imageable *> &target) const {
    verifyIsTessellated();
    triangleMesh.getPrimitives(target);
}

size_t SubdivisionSurfaceMesh::primitiveCount() const {
    verifyIsTessellated();
    return triangleMesh.primitiveCount();
}

void SubdivisionSurfaceMesh::tessellate() {
    CRAYG_TRACE_SCOPE("SubdivisionSurfaceMesh");
    OpenSubdivRefiner openSubdivRefiner(*this);
    openSubdivRefiner.refine(maxSubdivision);

    FanTriangulator fanTriangulator(*this);
    fanTriangulator.fanTriangulate(triangleMesh.faceVertexIndices);

    triangleMesh.points = points;
    triangleMesh.setMaterial(getMaterial());
    triangleMesh.setTransform(getTransform());
    copyNormalsToTriangleMesh();
    copyUvsToTriangleMesh();

    triangleMesh.init();

    points.clear();
    faceVertexIndices.clear();
    faceVertexCounts.clear();
    normals.clear();
    uvs.clear();
    uvIndices.clear();

    isTessellated = true;
}

std::size_t SubdivisionSurfaceMesh::faceCount() const {
    return faceVertexCounts.size();
}

void SubdivisionSurfaceMesh::copyNormalsToTriangleMesh() {
    auto primvar = triangleMesh.addNormalsPrimVar<TriangleMeshPerPointPrimVar<Vector3f>>();
    primvar->allocate();
    for (int i = 0; i < points.size(); i++) {
        primvar->write(i, normals[i]);
    }
}

bool SubdivisionSurfaceMesh::isTesselated() const {
    return isTessellated;
}

void SubdivisionSurfaceMesh::copyUvsToTriangleMesh() {
    if (!hasUvs()) {
        return;
    }
    auto uvPrimvar = triangleMesh.addUvsPrimVar<TriangleMeshPerVertexPrimVar<Vector2f>>();
    uvPrimvar->allocate();

    FanTriangulator uvFanTriangulator(uvIndices, faceVertexCounts);
    std::vector<TriangleMesh::FaceVertexIndices> triangulatedUvIndices;
    uvFanTriangulator.fanTriangulate(triangulatedUvIndices);

    for (int faceId = 0; faceId < triangulatedUvIndices.size(); faceId++) {
        auto faceIndices = triangulatedUvIndices[faceId];
        uvPrimvar->write(faceId, uvs[faceIndices.v0], uvs[faceIndices.v1], uvs[faceIndices.v2]);
    }
}

bool SubdivisionSurfaceMesh::hasUvs() const {
    return !uvs.empty() && !uvIndices.empty();
}
}