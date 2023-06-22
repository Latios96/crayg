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

    std::vector<size_t> ids;
    std::vector<Transform> transforms;
    std::vector<size_t> protoIndices;

    struct Prototype {
        std::vector<std::unique_ptr<Imageable>> members;
    };

    std::vector<std::unique_ptr<Prototype>> protos;
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_SCENE_PRIMITIVES_POINTINSTANCER_H_
