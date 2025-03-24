#pragma once

#include "basics/Vector3f.h"
#include <basics/Transform.h>

namespace crayg {

class Transformable {
  public:
    Transformable();
    explicit Transformable(const Transform &transform);
    explicit Transformable(const Vector3f &position);

    Vector3f getPosition() const {
        return transform.toPosition();
    }

    void setPosition(const Vector3f &position);

    const Transform &getTransform() const {
        return transform;
    }

    void setTransform(const Transform &transform);

  protected:
    Transform transform;
};

}
