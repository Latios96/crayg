#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_PRIMITIVES_POINTINSTANCER_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_PRIMITIVES_POINTINSTANCER_H_

#include "basics/Transform.h"
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

    std::vector<size_t> ids;
    std::vector<Transform> transforms;
    std::vector<size_t> protoIndices;

    struct Prototype {
        std::string name;
        std::vector<std::shared_ptr<SceneObject>> members;
    };

    std::vector<std::shared_ptr<Prototype>> protos;
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_SCENE_PRIMITIVES_POINTINSTANCER_H_
