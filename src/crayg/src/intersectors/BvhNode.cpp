//
// Created by Jan on 13.10.2021.
//

#include "BvhNode.h"
crayg::BvhNode::BvhNode(const crayg::BoundingBox &boundingBox,
                        crayg::BvhNode *left,
                        crayg::BvhNode *right,
                        const std::vector<SceneObject *> &objects)
    : boundingBox(boundingBox), left(left), right(right), objects(objects) {}
crayg::BvhNode::~BvhNode() {
    delete left;
    delete right;
}
bool crayg::BvhNode::operator==(const crayg::BvhNode &rhs) const {
    return boundingBox == rhs.boundingBox &&
        left == rhs.left &&
        right == rhs.right &&
        objects == rhs.objects;
}
bool crayg::BvhNode::operator!=(const crayg::BvhNode &rhs) const {
    return !(rhs == *this);
}
bool crayg::BvhNode::isLeaf() const {
    return left == nullptr && right == nullptr;
}
