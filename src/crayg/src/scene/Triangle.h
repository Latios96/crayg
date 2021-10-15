//
// Created by Jan Honsbrok on 12.11.18.
//

#ifndef CRAYG_TRIANGLE_H
#define CRAYG_TRIANGLE_H

#include <scene/Imageable.h>

namespace crayg {

class TriangleMesh;

struct BarycentricCoordinates {
    float alpha, beta, gamma;
};

class Triangle : public Imageable {
 public:
    Triangle();
    Triangle(TriangleMesh *triangleMesh, int faceIndex);

    bool isIntersecting(Ray ray) override;
    Imageable::Intersection intersect(Ray ray) override;
    Vector3f getNormal(Vector3f point) override;
    Vector3f getNormal();
    BoundingBox getBounds() const override;
    std::shared_ptr<Material> getMaterial() const override;

    Vector3f v0() const;
    Vector3f v1() const;
    Vector3f v2() const;

    TriangleMesh *triangleMesh;
    int faceIndex;

    BarycentricCoordinates toBarycentricCoordinates(const Vector3f &point);
    template<typename T>
    T interpolateLinear(const BarycentricCoordinates &coordinates, const T &value1, const T &value2, const T &value3);
 private:
    Intersection getIntersectionMullerTrumbore(const Ray &ray);
};

template<typename T>
T Triangle::interpolateLinear(const BarycentricCoordinates &coordinates,
                              const T &value1,
                              const T &value2,
                              const T &value3) {
    return value1 * coordinates.alpha + value2 * coordinates.beta + value3 * coordinates.gamma;
}

}

#endif //CRAYG_TRIANGLE_H
