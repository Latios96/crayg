#include "SubdivisionSurfaceMesh.h"
#include "OpenSubdivRefiner.h"
#include "FanTriangulator.h"
#include "scene/primitives/trianglemesh/primvars/TriangleMeshPerPointPrimVar.h"

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
        throw std::runtime_error("SubdivisionSurfaceMesh instance was not tesselated!");
    }
}
void SubdivisionSurfaceMesh::getPrimitives(std::vector<Imageable *> &target, bool *isOwning) const {
    verifyIsTessellated();
    triangleMesh.getPrimitives(target, isOwning);
}
size_t SubdivisionSurfaceMesh::primitiveCount() const {
    verifyIsTessellated();
    return triangleMesh.primitiveCount();
}

void SubdivisionSurfaceMesh::tessellate() {
    OpenSubdivRefiner openSubdivRefiner(*this);
    openSubdivRefiner.refine();

    FanTriangulator fanTriangulator(*this);
    fanTriangulator.fanTriangulate(triangleMesh.faceVertexIndices);

    triangleMesh.points = points;
    triangleMesh.setMaterial(getMaterial());
    triangleMesh.setTransform(getTransform());
    copyNormalsToTriangleMesh();

    triangleMesh.init();

    points.clear();
    faceVertexIndices.clear();
    faceVertexCounts.clear();
    normals.clear();

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
} // crayg