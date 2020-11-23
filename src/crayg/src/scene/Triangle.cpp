//
// Created by Jan Honsbrok on 12.11.18.
//

#include <iostream>
#include "Triangle.h"
#include "TriangleMesh.h"

namespace crayg {

Vector3f Triangle::v0() {
    return triangleMesh->points[triangleMesh->faceIndexes[faceIndex]];
}
Vector3f Triangle::v1() {
    return triangleMesh->points[triangleMesh->faceIndexes[faceIndex + 1]];
}
Vector3f Triangle::v2() {
    return triangleMesh->points[triangleMesh->faceIndexes[faceIndex + 2]];
}

Triangle::Intersection Triangle::intersect(Ray ray) {

    return getIntersectionMullerTrumbore(ray);
}

Imageable::Intersection Triangle::getIntersectionMullerTrumbore(const Ray &ray) {
    //Vec3 v0v1 = sub(*v1, *v0);
    Vector3f v0v1 = v1() - v0();

    //Vec3 v0v2 = sub(*v2, *v0);
    Vector3f v0v2 = v2() - v0();

    //Vec3 pvec = cross(r->dir, v0v2);
    Vector3f pvec = ray.direction.crossProduct(v0v2);

    //float det = dot(v0v1, pvec);
    float det = v0v1.scalarProduct(pvec);

    if (det < 0.000001) {
        return {std::numeric_limits<float>::max(), nullptr};
    }

    float invDet = 1.0f / det;

    //Vec3 tvec = sub(r->orig, *v0);
    Vector3f tvec = ray.startPoint - v0();

    //float u = dot(tvec, pvec) * invDet;
    float u = tvec.scalarProduct(pvec) * invDet;

    if (u < 0 || u > 1) {
        return {std::numeric_limits<float>::max(), nullptr};
    }

    //Vec3 qvec = cross(tvec, v0v1);
    Vector3f qvec = tvec.crossProduct(v0v1);

    //float v = dot(r->dir, qvec) * invDet;
    float v = ray.direction.scalarProduct(qvec) * invDet;

    if (v < 0 || u + v > 1) {
        return {std::numeric_limits<float>::max(), nullptr};
    }
    // dot(v0v2, qvec) * invDet;
    return {v0v2.scalarProduct(qvec) * invDet, shared_from_this()};
}
bool Triangle::isIntersecting(Ray ray) {
    Vector3f normal = (v1() - v0()).crossProduct((v2() - v0()));

    const float scalar = normal.scalarProduct(ray.direction);

    const bool raysAreParallel = scalar == 0;

    if (raysAreParallel) {
        return false;
    } else {
        const float t = -(normal.scalarProduct(ray.startPoint) + v0().length()) / scalar;

        if (t > 0) {
            Vector3f hitLocation = ray.startPoint + (ray.direction * t);

            Vector3f C;

            // do inside / outside tests

            Vector3f edge0 = v1() - v0();
            Vector3f vp0 = hitLocation - v0();
            C = edge0.crossProduct(vp0);
            if (normal.scalarProduct(C) < 0) {
                return false;
            }

            Vector3f edge1 = v2() - v1();
            Vector3f vp1 = hitLocation - v1();
            C = edge1.crossProduct(vp1);
            if (normal.scalarProduct(C) < 0) {
                return false;
            }

            Vector3f edge2 = v0() - v2();
            Vector3f vp2 = hitLocation - v2();
            C = edge2.crossProduct(vp2);
            if (normal.scalarProduct(C) < 0) {
                return false;
            }
            return true;

        }
        return false;
    }
}

Triangle::Triangle(
    TriangleMesh *triangleMesh,
    int faceIndex)
    : triangleMesh(triangleMesh), faceIndex(faceIndex) {
    setMaterial(triangleMesh->getMaterial());
}

Triangle::Triangle() {
    triangleMesh = nullptr;
    faceIndex = 0;
}

Vector3f Triangle::getNormal(Vector3f point) {
    auto barycentric = toBarycentricCoordinates(point);

    auto normalV0 = triangleMesh->normals[triangleMesh->faceIndexes[faceIndex]];
    auto normalV1 = triangleMesh->normals[triangleMesh->faceIndexes[faceIndex + 1]];
    auto normalV2 = triangleMesh->normals[triangleMesh->faceIndexes[faceIndex + 2]];

    return interpolateLinear(barycentric, normalV0, normalV1, normalV2).normalize();
}

Vector3f Triangle::getNormal() {
    const Vector3f normal = (v2() - v0()).crossProduct(v1() - v0()).normalize();
    return normal.invert();
}
BarycentricCoordinates Triangle::toBarycentricCoordinates(const Vector3f &point) {
    // based on Fundamentals of Computer Graphics, 2016, p. 49
    const Vector3f &normal = getNormal();
    float lengthSquared = normal.lengthSquared();
    float alpha = normal.scalarProduct((v2() - v1()).crossProduct(point - v1())) / lengthSquared;
    float beta = normal.scalarProduct((v0() - v2()).crossProduct(point - v2())) / lengthSquared;
    float gamma = normal.scalarProduct((v1() - v0()).crossProduct(point - v0())) / lengthSquared;
    return {alpha, beta, gamma};
}

}

