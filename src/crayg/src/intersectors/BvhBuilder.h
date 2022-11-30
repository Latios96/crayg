#ifndef CRAYG_SRC_CRAYG_SRC_INTERSECTORS_BVHBUILDER_H_
#define CRAYG_SRC_CRAYG_SRC_INTERSECTORS_BVHBUILDER_H_
#include <scene/Scene.h>
#include "BvhNode.h"
namespace crayg {

struct Bvh {
    Bvh() = default;
    Bvh(BvhNode *root);
    BvhNode *root;
    std::vector<Imageable *> objects;
    std::vector<std::pair<std::size_t, std::size_t>> objectsToFree;
    virtual ~Bvh();
};

class BvhBuilder {
 public:
    BvhBuilder(const Scene &scene);
    const Scene &scene;
    [[nodiscard]] Bvh *build() const;
 private:
    void collectPrimitives(Bvh *bvh);
    int collectPrimitiveCount();
};
}

#endif //CRAYG_SRC_CRAYG_SRC_INTERSECTORS_BVHBUILDER_H_
