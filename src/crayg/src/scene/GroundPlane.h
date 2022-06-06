//
// Created by Jan Honsbrok on 07.11.18.
//

#ifndef CRAYG_GROUNDPLANE_H
#define CRAYG_GROUNDPLANE_H

#include "SceneObject.h"

namespace crayg {

class GroundPlane : public SceneObject {
 public:
    Imageable::Intersection intersect(Ray ray) override;

    bool isIntersecting(Ray ray) override;

    Vector3f getNormal(Vector3f point) override;
    BoundingBox getBounds() const override;
    std::string getType() override;
 private:
    Vector3f normal = Vector3f(0, 1, 0);
};

}

#endif //CRAYG_GROUNDPLANE_H
