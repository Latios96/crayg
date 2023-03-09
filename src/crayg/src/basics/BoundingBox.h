#ifndef CRAYG_BOUNDINGBOX_H
#define CRAYG_BOUNDINGBOX_H

#include "Ray.h"
#include "Vector3f.h"
#include <fmt/ostream.h>
#include <ostream>

namespace crayg {

class BoundingBox {

  public:
    BoundingBox();
    BoundingBox(const Vector3f &min, const Vector3f &max);
    static BoundingBox fromCenterAndRadius(const Vector3f &center, const float radius);

    bool operator==(const BoundingBox &rhs) const;

    bool operator!=(const BoundingBox &rhs) const;

    Vector3f min, max;

    bool isIntersecting(const Ray &ray) const;

    BoundingBox unionWith(const Vector3f &point) const;
    BoundingBox unionWith(const BoundingBox &boundingBox) const;

    Vector3f getCentroid() const;

    friend std::ostream &operator<<(std::ostream &os, const BoundingBox &box);
};

}

template <> struct fmt::formatter<crayg::BoundingBox> : ostream_formatter {};

#endif // CRAYG_BOUNDINGBOX_H
