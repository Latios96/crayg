//
// Created by Jan Honsbrok on 12.11.18.
//

#ifndef CRAYG_TRIANGLE_H
#define CRAYG_TRIANGLE_H


#include <intersectors/Intersectable.h>

class Triangle : public Intersectable{
public:
    Triangle();
    Triangle(const Vector3f v0, const Vector3f v1, const Vector3f v2);

    bool intersects(Ray ray) override;
    Ray intersect(Ray ray) override;

private:
    Vector3f v0, v1, v2;
};


#endif //CRAYG_TRIANGLE_H
