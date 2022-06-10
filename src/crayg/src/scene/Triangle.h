//
// Created by Jan Honsbrok on 12.11.18.
//

#ifndef CRAYG_TRIANGLE_H
#define CRAYG_TRIANGLE_H

#include <scene/Imageable.h>

namespace crayg {

class TriangleMesh;

class Triangle : public Imageable {
 public:
    Triangle();
    Triangle(TriangleMesh *triangleMesh, int faceIndex);

    bool isIntersecting(Ray ray) override;
    Imageable::Intersection intersect(Ray ray) override;
    Vector3f getNormal(Vector3f point) override;
    Vector3f getNormal() const;
    BoundingBox getBounds() const override;
    std::shared_ptr<Material> getMaterial() const override;

    Vector3f v0() const;
    Vector3f v1() const;
    Vector3f v2() const;

    TriangleMesh *triangleMesh;
    int faceIndex;

 private:
    Intersection getIntersectionMullerTrumbore(const Ray &ray);
};

}

#endif //CRAYG_TRIANGLE_H
