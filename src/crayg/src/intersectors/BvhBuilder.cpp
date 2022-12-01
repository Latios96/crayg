#include "BvhBuilder.h"
#include "utils/StopWatch.h"
namespace crayg {

enum Axis {
    X, Y, Z
};

struct SplitInfo {
    Axis axis;
    float splitPoint;
    SplitInfo(Axis axis, float splitPoint) : axis(axis), splitPoint(splitPoint) {}
};

SplitInfo getSplitInfo(const BoundingBox &bounds) {
    const Vector3f length = bounds.max - bounds.min;
    if (length.x >= length.y && length.x >= length.z) {
        return {Axis::X, bounds.min.x + (length.x / 2.0f)};
    } else if (length.y >= length.x && length.y >= length.z) {
        return {Axis::Y, bounds.min.y + (length.y / 2.0f)};
    } else {
        return {Axis::Z, bounds.min.z + (length.z / 2.0f)};
    }
}

BoundingBox computeBounds(const std::vector<Imageable *> &objects) {
    if (objects.empty()) {
        return {};
    }
    auto boundingBox = objects[0]->getBounds();
    for (const auto &obj: objects) {
        boundingBox = boundingBox.unionWith(obj->getBounds());
    }
    return boundingBox;
}

BoundingBox computeCentroidBounds(const std::vector<Imageable *> &objects) {
    if (objects.empty()) {
        return {};
    }
    BoundingBox boundingBox(objects[0]->getBounds().getCentroid(), objects[0]->getBounds().getCentroid());
    for (const auto &obj: objects) {
        const Vector3f objCentroid = obj->getBounds().getCentroid();
        boundingBox = boundingBox.unionWith(objCentroid);
    }
    return boundingBox;
}
bool isLeft(const Imageable *obj, const SplitInfo &splitInfo) {
    if (splitInfo.axis == Axis::X) {
        return obj->getBounds().getCentroid().x < splitInfo.splitPoint;
    } else if (splitInfo.axis == Axis::Y) {
        return obj->getBounds().getCentroid().y < splitInfo.splitPoint;
    } else {
        return obj->getBounds().getCentroid().z < splitInfo.splitPoint;
    }
}

std::unique_ptr<BvhNode> buildTree(const std::vector<Imageable *> &objects) {
    const auto bounds = computeBounds(objects);
    std::vector<Imageable *> left, right;
    const BoundingBox centroidBounds = computeCentroidBounds(objects);
    const SplitInfo splitInfo = getSplitInfo(centroidBounds);

    for (const auto &obj: objects) {
        if (isLeft(obj, splitInfo)) {
            left.push_back(obj);
        } else {
            right.push_back(obj);
        }
    }
    if (objects.size() == left.size() || objects.size() == right.size()) {
        return std::make_unique<BvhNode>(bounds, nullptr, nullptr, objects);
    }

    return std::make_unique<BvhNode>(bounds,
                                     !left.empty() ? buildTree(left) : nullptr,
                                     !right.empty() ? buildTree(right) : nullptr,
                                     std::vector<Imageable *>());
}

std::unique_ptr<Bvh> BvhBuilder::build() const {
    InformativeScopedStopWatch informativeScopedStopWatch("Building BVH");
    Logger::info("Objects in scene: {:L}", scene.objects.size());

    auto bvh = std::make_unique<Bvh>();

    collectPrimitives(*bvh);

    {
        InformativeScopedStopWatch buildingBvh("Building BVH");
        bvh->root = buildTree(bvh->objects);
    }

    return bvh;
}
void BvhBuilder::collectPrimitives(Bvh &bvh) const {
    InformativeScopedStopWatch collectingPrimitives("Collecting primitives");

    int primitiveCount = collectPrimitiveCount();
    Logger::info("Primitives in scene: {:L}", primitiveCount);

    bvh.objects.reserve(primitiveCount);

    for (int i = 0; i < scene.objects.size(); i++) {
        auto &obj = scene.objects[i];
        bool isOwning;
        size_t startIndex = bvh.objects.size();
        obj->getPrimitives(bvh.objects, &isOwning);
        if (isOwning) {
            bvh.objectsToFree.emplace_back(startIndex);
        }
    }
}
int BvhBuilder::collectPrimitiveCount() const {
    int primitiveCount = 0;
    InformativeScopedStopWatch collectingPrimitiveCount("Collecting primitive count");
    for (auto &obj: scene.objects) {
        primitiveCount += obj->primitiveCount();
    }
    return primitiveCount;
}
BvhBuilder::BvhBuilder(const Scene &scene) : scene(scene) {}

Bvh::~Bvh() {
    for (auto objectsToFreeInfo: objectsToFree) {
        Triangle *triangle = dynamic_cast<Triangle *>(objects[objectsToFreeInfo]);
        delete[] triangle;
    }
}
Bvh::Bvh(std::unique_ptr<BvhNode> root) : root(std::move(root)) {

}
}
