#ifndef CRAYG_RAY_H
#define CRAYG_RAY_H

#include "Vector3f.h"
#include <fmt/ostream.h>
#include <ostream>

namespace crayg {

struct Ray {
    Vector3f startPoint, direction;
    float length;

  public:
    Ray(Vector3f startPoint, Vector3f direction);

    Ray(Vector3f startPoint, Vector3f direction, float length);

    static Ray createInvalid();

    bool isValid();

    Vector3f constructIntersectionPoint() const;

    Vector3f constructIntersectionPoint(float t) const;

    Ray offsetStartPointBy(float offset) const;

    bool operator==(const Ray &rhs) const;
    bool operator!=(const Ray &rhs) const;
    friend std::ostream &operator<<(std::ostream &os, const Ray &ray);
};

}

template <> struct fmt::formatter<crayg::Ray> : ostream_formatter {};

#endif // CRAYG_RAY_H
