#include "BvhNode.h"
crayg::BvhNode::BvhNode(const crayg::BoundingBox &boundingBox,
                        std::unique_ptr<BvhNode> left,
                        std::unique_ptr<BvhNode> right,
                        const std::vector<Imageable *> &objects)
    : boundingBox(boundingBox), left(std::move(left)), right(std::move(right)), objects(objects) {}

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
