#pragma once

#include "crayg/foundation/math/geometry/Transform.h"
#include "scene/Imageable.h"
#include "scene/SceneObject.h"
#include <vector>

namespace crayg {

class PointInstancer : public SceneObject {
  public:
    std::string getType() override;
    virtual ~PointInstancer() = default;
    Vector3f getNormal(Vector3f point) override;
    Intersection intersect(Ray ray) override;
    bool isIntersecting(Ray ray) override;
    BoundingBox getBounds() const override;

    void init();

    std::vector<size_t> ids;
    std::vector<Transform> transforms;
    std::vector<size_t> protoIndices;

    struct Prototype {
        std::string name;
        std::vector<std::shared_ptr<SceneObject>> members;
    };

    std::vector<std::shared_ptr<Prototype>> protos;
};

}
