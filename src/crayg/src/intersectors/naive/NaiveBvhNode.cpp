#include "NaiveBvhNode.h"
#include "scene/primitives/trianglemesh/Triangle.h"

crayg::NaiveBvh::~NaiveBvh() {
    for (auto objectsToFreeInfo : objectsToFree) {
        Triangle *triangle = dynamic_cast<Triangle *>(objects[objectsToFreeInfo]);
        delete[] triangle;
    }
}

crayg::NaiveBvh::NaiveBvh(std::unique_ptr<NaiveBvhNode> root) : root(std::move(root)) {
}

crayg::NaiveBvhNode::NaiveBvhNode(const crayg::BoundingBox &boundingBox, std::unique_ptr<NaiveBvhNode> left,
                                  std::unique_ptr<NaiveBvhNode> right, const std::vector<Imageable *> &objects)
    : boundingBox(boundingBox), left(std::move(left)), right(std::move(right)), objects(objects) {
}

bool crayg::NaiveBvhNode::operator==(const crayg::NaiveBvhNode &rhs) const {
    return boundingBox == rhs.boundingBox && left == rhs.left && right == rhs.right && objects == rhs.objects;
}

bool crayg::NaiveBvhNode::operator!=(const crayg::NaiveBvhNode &rhs) const {
    return !(rhs == *this);
}

bool crayg::NaiveBvhNode::isLeaf() const {
    return left == nullptr && right == nullptr;
}
