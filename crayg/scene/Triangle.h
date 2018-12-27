//
// Created by Jan Honsbrok on 12.11.18.
//

#ifndef CRAYG_TRIANGLE_H
#define CRAYG_TRIANGLE_H

#include <scene/Imageable.h>

class Triangle : public Imageable{
public:
    static int intersections;
    Triangle();
    Triangle(const Vector3f v0, const Vector3f v1, const Vector3f v2);

    bool isIntersecting(Ray ray) override;
    Imageable::Intersection intersect(Ray ray) override;
    Vector3f getNormal(Vector3f point) override;

private:
    // todo store only face indices
    Vector3f v0, v1, v2;

    Intersection getIntersectionMyImpl(const Ray &ray);

    Intersection getIntersectionMullerTrumbore(const Ray &ray);
};


#endif //CRAYG_TRIANGLE_H
