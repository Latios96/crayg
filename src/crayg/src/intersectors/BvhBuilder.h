#ifndef CRAYG_SRC_CRAYG_SRC_INTERSECTORS_BVHBUILDER_H_
#define CRAYG_SRC_CRAYG_SRC_INTERSECTORS_BVHBUILDER_H_
#include <scene/Scene.h>
#include "BvhNode.h"
namespace crayg {

struct Bvh {
    Bvh() = default;
    Bvh(std::unique_ptr<BvhNode> root);
    std::unique_ptr<BvhNode> root;
    std::vector<Imageable *> objects;
    std::vector<int> objectsToFree;
    virtual ~Bvh();
};

class BvhBuilder {
 public:
    BvhBuilder(const Scene &scene);
    const Scene &scene;
    std::unique_ptr<Bvh> build() const;
 private:
    void collectPrimitives(Bvh &bvh) const;
    int collectPrimitiveCount() const;
};
}

#endif //CRAYG_SRC_CRAYG_SRC_INTERSECTORS_BVHBUILDER_H_
