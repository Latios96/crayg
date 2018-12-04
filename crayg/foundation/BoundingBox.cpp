//
// Created by jan on 02.12.18.
//

#include "BoundingBox.h"

BoundingBox::BoundingBox(const Vector3f &min, const Vector3f &max) : min(min), max(max) {}

bool BoundingBox::operator==(const BoundingBox &rhs) const {
    return min == rhs.min &&
           max == rhs.max;
}

bool BoundingBox::operator!=(const BoundingBox &rhs) const {
    return !(rhs == *this);
}

BoundingBox::BoundingBox() {
    min = Vector3f();
    max = Vector3f();
}


