//
// Created by jan on 02.12.18.
//

#ifndef CRAYG_BOUNDINGBOX_H
#define CRAYG_BOUNDINGBOX_H

#include <ostream>
#include "Vector3f.h"
#include "Ray.h"

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
 private:
    void unite(BoundingBox &boundingBox, const Vector3f &point) const;
};

}

#endif //CRAYG_BOUNDINGBOX_H
