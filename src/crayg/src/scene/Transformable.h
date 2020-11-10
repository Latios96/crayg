//
// Created by jan on 22.08.18.
//

#ifndef CRAYG_TRANSFORMABLE_H
#define CRAYG_TRANSFORMABLE_H

#include <basics/Transform.h>
#include "basics/Vector3f.h"

class Transformable {
 public:
    Transformable();
    explicit Transformable(const Vector3f &position);

    Vector3f getPosition() const;
    void setPosition(const Vector3f &position);

    const Transform getTransform() const;

 protected:
    Transform transform;
};

#endif //CRAYG_TRANSFORMABLE_H
