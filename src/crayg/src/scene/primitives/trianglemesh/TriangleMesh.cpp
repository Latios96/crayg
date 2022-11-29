#include "TriangleMesh.h"
#include "scene/primitives/trianglemesh/primvars/TriangleMeshPerFacePrimVar.h"
#include "scene/primitives/trianglemesh/primvars/TriangleMeshPerVertexPrimVar.h"

namespace crayg {

bool TriangleMesh::isIntersecting(Ray ray) {
    return false;
}

Imageable::Intersection TriangleMesh::intersect(Ray ray) {
    if (boundingBox.isIntersecting(ray)) {
        Imageable::Intersection hitIntersection(std::numeric_limits<float>::max(), nullptr);

        for (auto id: faceIds()) {
            Triangle triangle(this, id);
            Imageable::Intersection intersection = triangle.intersect(ray);
            hitIntersection = Imageable::Intersection::nearest(intersection, hitIntersection);
        }
        return hitIntersection;
    } else {
        return {std::numeric_limits<float>::max(), nullptr};
    }
}

void TriangleMesh::getTriangles(std::vector<std::shared_ptr<Imageable>> &triangles) {
    for (auto id: faceIds()) {
        triangles.push_back(std::make_shared<Triangle>(this, id));
    }
}

Vector3f TriangleMesh::getNormal(Vector3f point) {
    return {0, 1, 0};
}

void TriangleMesh::createCube(TriangleMesh &mesh) {
    mesh.points.emplace_back(-1.0f, -1.0f, 1.0f);
    mesh.points.emplace_back(-1.0f, -1.0f, 1.0f);
    mesh.points.emplace_back(-1.0f, 1.0f, 1.0f);
    mesh.points.emplace_back(1.0f, 1.0f, 1.0f);
    mesh.points.emplace_back(-1.0f, 1.0f, -1.0f);
    mesh.points.emplace_back(1.0f, 1.0f, -1.0f);
    mesh.points.emplace_back(-1.0f, -1.0f, -1.0f);
    mesh.points.emplace_back(1.0f, -1.0f, -1.0f);

    mesh.faceVertexIndices.emplace_back(0, 1, 2);
    mesh.faceVertexIndices.emplace_back(2, 1, 3);
    mesh.faceVertexIndices.emplace_back(2, 3, 4);
    mesh.faceVertexIndices.emplace_back(4, 3, 5);
    mesh.faceVertexIndices.emplace_back(4, 5, 6);
    mesh.faceVertexIndices.emplace_back(6, 5, 7);
    mesh.faceVertexIndices.emplace_back(6, 7, 0);
    mesh.faceVertexIndices.emplace_back(0, 7, 1);
    mesh.faceVertexIndices.emplace_back(1, 7, 3);
    mesh.faceVertexIndices.emplace_back(3, 7, 5);
    mesh.faceVertexIndices.emplace_back(6, 0, 4);
    mesh.faceVertexIndices.emplace_back(4, 0, 2);
}

void TriangleMesh::createBounds() {
    Vector3f min, max;
    for (const auto &point: points) {
        if (point.x < min.x) {
            min.x = point.x;
        }
        if (point.y < min.y) {
            min.y = point.y;
        }
        if (point.z < min.z) {
            min.z = point.z;
        }

        if (point.x > max.x) {
            max.x = point.x;
        }
        if (point.y > max.y) {
            max.y = point.y;
        }
        if (point.z > max.z) {
            max.z = point.z;
        }
    }
    boundingBox = BoundingBox(min, max);
}
void TriangleMesh::createNormals() {
    if (normalsPrimVar == nullptr) {
        auto primVar = addNormalsPrimVar<TriangleMeshPerFacePrimVar<Vector3f>>();
        for (auto id: faceIds()) {
            Triangle triangle(this, id);
            const Vector3f normal = triangle.getNormal();
            primVar->write(id, normal);
        }
    } else {
        normalsPrimVar->apply([this](Vector3f normal) {
            return transform.applyForNormal(normal);
        });
    }

}
BoundingBox TriangleMesh::getBounds() const {
    return boundingBox;
}
void TriangleMesh::init() {
    for (auto &point: points) {
        point = transform.apply(point);
    } // todo check if this is necessary
    createBounds();
    createNormals();
}
std::string TriangleMesh::getType() {
    return "TriangleMesh";
}
TriangleMesh::TriangleMesh() : normalsPrimVar(nullptr) {
}
int TriangleMesh::faceCount() const {
    return faceVertexIndices.size();
}

TriangleMesh::FaceVertexIndices::FaceVertexIndices(int v0, int v1, int v2) : v0(v0), v1(v1), v2(v2) {}
bool TriangleMesh::FaceVertexIndices::operator==(const TriangleMesh::FaceVertexIndices &rhs) const {
    return v0 == rhs.v0 &&
        v1 == rhs.v1 &&
        v2 == rhs.v2;
}
bool TriangleMesh::FaceVertexIndices::operator!=(const TriangleMesh::FaceVertexIndices &rhs) const {
    return !(rhs == *this);
}

TriangleMesh::FaceIdIterator TriangleMesh::FaceIdIterator::operator++() {
    return FaceIdIterator(++id);
}

std::size_t TriangleMesh::FaceIdIterator::operator*() const { return id; }

bool TriangleMesh::FaceIdIterator::operator!=(const TriangleMesh::FaceIdIterator &o) const {
    return id != o.id;
}

TriangleMesh::FaceIdIterator TriangleMesh::FaceIdIteratorAdapter::begin() {
    return {0};
}

TriangleMesh::FaceIdIterator TriangleMesh::FaceIdIteratorAdapter::end() {
    return {triangleMesh.faceVertexIndices.size()};
}

TriangleMesh::FaceIdIteratorAdapter TriangleMesh::faceIds() const {
    return {*const_cast<TriangleMesh *>(this)};
}
void TriangleMesh::getPrimitives(std::vector<Imageable *> &target, bool *isOwning) {
    target.reserve(target.size() + faceCount());
    for (auto id: faceIds()) {
        target.push_back(new Triangle(this, id));
    }
    *isOwning = true;
}

}
