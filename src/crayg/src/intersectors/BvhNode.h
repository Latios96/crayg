//
// Created by Jan on 13.10.2021.
//

#ifndef CRAYG_SRC_CRAYG_SRC_INTERSECTORS_BVHNODE_H_
#define CRAYG_SRC_CRAYG_SRC_INTERSECTORS_BVHNODE_H_
#include <basics/BoundingBox.h>
#include <scene/SceneObject.h>
namespace crayg {

class BvhNode {
 public:
    BvhNode(const BoundingBox &boundingBox, BvhNode *left, BvhNode *right, const std::vector<Imageable *> &objects);
    BoundingBox boundingBox;
    BvhNode *left;
    BvhNode *right;
    std::vector<Imageable *> objects;

    bool isLeaf() const;

    bool operator==(const BvhNode &rhs) const;
    bool operator!=(const BvhNode &rhs) const;

    virtual ~BvhNode();
};
}
#endif //CRAYG_SRC_CRAYG_SRC_INTERSECTORS_BVHNODE_H_
