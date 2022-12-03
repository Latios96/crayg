#ifndef CRAYG_SRC_CRAYG_SRC_INTERSECTORS_BVHNODE_H_
#define CRAYG_SRC_CRAYG_SRC_INTERSECTORS_BVHNODE_H_

#include <vector>
#include <basics/BoundingBox.h>
#include <scene/SceneObject.h>

namespace crayg {

class NaiveBvhNode {
 public:
    NaiveBvhNode(const BoundingBox &boundingBox,
                 std::unique_ptr<NaiveBvhNode> left,
                 std::unique_ptr<NaiveBvhNode> right,
                 const std::vector<Imageable *> &objects);
    BoundingBox boundingBox;
    std::unique_ptr<NaiveBvhNode> left;
    std::unique_ptr<NaiveBvhNode> right;
    std::vector<Imageable *> objects;

    bool isLeaf() const;

    bool operator==(const NaiveBvhNode &rhs) const;
    bool operator!=(const NaiveBvhNode &rhs) const;
};

struct NaiveBvh {
    NaiveBvh() = default;
    NaiveBvh(std::unique_ptr<NaiveBvhNode> root);
    std::unique_ptr<NaiveBvhNode> root;
    std::vector<Imageable *> objects;
    std::vector<int> objectsToFree;
    virtual ~NaiveBvh();
};

}
#endif //CRAYG_SRC_CRAYG_SRC_INTERSECTORS_BVHNODE_H_
