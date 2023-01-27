#include "SubdivisionSurfaceMesh.h"

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
    // TODO check if transform and material is set correctly for triangle mesh
    isTessellated = true;
}
std::size_t SubdivisionSurfaceMesh::faceCount() const {
    return faceVertexCounts.size();
}
} // crayg