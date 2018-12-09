//
// Created by jan on 02.12.18.
//

#ifndef CRAYG_BOUNDINGBOX_H
#define CRAYG_BOUNDINGBOX_H


#include <ostream>
#include "Vector3f.h"

class BoundingBox {

public:
    BoundingBox();
    BoundingBox(const Vector3f &min, const Vector3f &max);

    bool operator==(const BoundingBox &rhs) const;

    bool operator!=(const BoundingBox &rhs) const;

    Vector3f min, max;
};


#endif //CRAYG_BOUNDINGBOX_H
