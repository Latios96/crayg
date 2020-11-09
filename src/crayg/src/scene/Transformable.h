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
    Transformable(const Vector3f &position);

    Vector3f getPosition() const;

    void setPosition(const Vector3f &position);

 private:
    Vector3f position;
    Transform transform;
};

#endif //CRAYG_TRANSFORMABLE_H
