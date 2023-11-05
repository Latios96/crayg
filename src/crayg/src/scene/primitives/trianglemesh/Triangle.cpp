#include "Triangle.h"
#include "TriangleMesh.h"
#include <iostream>

namespace crayg {

Vector3f &Triangle::v0() const {
    return triangleMesh->points[triangleMesh->faceVertexIndices[faceId].v0];
}

Vector3f &Triangle::v1() const {
    return triangleMesh->points[triangleMesh->faceVertexIndices[faceId].v1];
}

Vector3f &Triangle::v2() const {
    return triangleMesh->points[triangleMesh->faceVertexIndices[faceId].v2];
}

Triangle::Intersection Triangle::intersect(Ray ray) {
    return getIntersectionMullerTrumbore(ray);
}

Imageable::Intersection Triangle::getIntersectionMullerTrumbore(const Ray &ray) {
    // Vec3 v0v1 = sub(*v1, *v0);
    Vector3f v0v1 = v1() - v0();

    // Vec3 v0v2 = sub(*v2, *v0);
    Vector3f v0v2 = v2() - v0();

    // Vec3 pvec = cross(r->dir, v0v2);
    Vector3f pvec = ray.direction.cross(v0v2);

    // float det = dot(v0v1, pvec);
    float det = v0v1.dot(pvec);

    if (det < 0.000001) {
        return {std::numeric_limits<float>::max(), nullptr};
    }

    float invDet = 1.0f / det;

    // Vec3 tvec = sub(r->orig, *v0);
    Vector3f tvec = ray.startPoint - v0();

    // float u = dot(tvec, pvec) * invDet;
    float u = tvec.dot(pvec) * invDet;

    if (u < 0 || u > 1) {
        return {std::numeric_limits<float>::max(), nullptr};
    }

    // Vec3 qvec = cross(tvec, v0v1);
    Vector3f qvec = tvec.cross(v0v1);

    // float v = dot(r->dir, qvec) * invDet;
    float v = ray.direction.dot(qvec) * invDet;

    if (v < 0 || u + v > 1) {
        return {std::numeric_limits<float>::max(), nullptr};
    }
    // dot(v0v2, qvec) * invDet;
    return {v0v2.dot(qvec) * invDet, this};
}

bool Triangle::isIntersecting(Ray ray) {
    Vector3f normal = (v1() - v0()).cross((v2() - v0()));

    const float scalar = normal.dot(ray.direction);

    const bool raysAreParallel = scalar == 0;

    if (raysAreParallel) {
        return false;
    } else {
        const float t = -(normal.dot(ray.startPoint) + v0().length()) / scalar;

        if (t > 0) {
            Vector3f hitLocation = ray.startPoint + (ray.direction * t);

            Vector3f C;

            // do inside / outside tests

            Vector3f edge0 = v1() - v0();
            Vector3f vp0 = hitLocation - v0();
            C = edge0.cross(vp0);
            if (normal.dot(C) < 0) {
                return false;
            }

            Vector3f edge1 = v2() - v1();
            Vector3f vp1 = hitLocation - v1();
            C = edge1.cross(vp1);
            if (normal.dot(C) < 0) {
                return false;
            }

            Vector3f edge2 = v0() - v2();
            Vector3f vp2 = hitLocation - v2();
            C = edge2.cross(vp2);
            if (normal.dot(C) < 0) {
                return false;
            }
            return true;
        }
        return false;
    }
}

Vector3f Triangle::getNormal(Vector3f point) {
    if (instanceTransform) {
        point = instanceTransform->applyInverseForPoint(point);
    }
    return this->triangleMesh->normalsPrimVar->interpolateAt(this->faceId, point).normalize();
}

Vector3f Triangle::getNormal() const {
    const Vector3f normal = (v2() - v0()).cross(v1() - v0()).normalize();
    return normal.invert();
}

BoundingBox Triangle::getBounds() const {
    BoundingBox boundingBox(v0(), v0());
    boundingBox = boundingBox.unionWith(v1());
    boundingBox = boundingBox.unionWith(v2());
    return boundingBox;
}

std::shared_ptr<Material> &Triangle::getMaterial() {
    return triangleMesh->getMaterial();
}

}
