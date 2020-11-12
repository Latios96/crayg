//
// Created by Jan Honsbrok on 12.11.18.
//

#ifndef CRAYG_TRIANGLE_H
#define CRAYG_TRIANGLE_H

#include <scene/Imageable.h>

class TriangleMesh;

class Triangle : public Imageable {
 public:
    Triangle();
    Triangle(TriangleMesh *triangleMesh, int faceIndex);

    bool isIntersecting(Ray ray) override;
    Imageable::Intersection intersect(Ray ray) override;
    Vector3f getNormal(Vector3f point) override;
    Vector3f getNormal();

    Vector3f v0();
    Vector3f v1();
    Vector3f v2();

    TriangleMesh *triangleMesh;
    int faceIndex;
 private:
    Intersection getIntersectionMullerTrumbore(const Ray &ray);

};

#endif //CRAYG_TRIANGLE_H
