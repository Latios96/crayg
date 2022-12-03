#ifndef CRAYG_SRC_CRAYG_SRC_INTERSECTORS_BVHNODE_H_
#define CRAYG_SRC_CRAYG_SRC_INTERSECTORS_BVHNODE_H_

#include <vector>
#include <basics/BoundingBox.h>
#include <scene/SceneObject.h>

namespace crayg {

class BvhNode {
 public:
    BvhNode(const BoundingBox &boundingBox,
            std::unique_ptr<BvhNode> left,
            std::unique_ptr<BvhNode> right,
            const std::vector<Imageable *> &objects);
    BoundingBox boundingBox;
    std::unique_ptr<BvhNode> left;
    std::unique_ptr<BvhNode> right;
    std::vector<Imageable *> objects;

    bool isLeaf() const;

    bool operator==(const BvhNode &rhs) const;
    bool operator!=(const BvhNode &rhs) const;
};

struct Bvh {
    Bvh() = default;
    Bvh(std::unique_ptr<BvhNode> root);
    std::unique_ptr<BvhNode> root;
    std::vector<Imageable *> objects;
    std::vector<int> objectsToFree;
    virtual ~Bvh();
};

}
#endif //CRAYG_SRC_CRAYG_SRC_INTERSECTORS_BVHNODE_H_
