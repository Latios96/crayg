//
// Created by Jan on 13.10.2021.
//

#include "BvhBuilder.h"
namespace crayg {

enum Axis {
    X, Y, Z
};

struct SplitInfo {
    Axis axis;
    float splitPoint;
    SplitInfo(Axis axis, float splitPoint) : axis(axis), splitPoint(splitPoint) {}
};

SplitInfo getSplitInfo(const crayg::BoundingBox &bounds) {
    const crayg::Vector3f length = bounds.max - bounds.min;
    if (length.x >= length.y && length.x >= length.z) {
        return {Axis::X, bounds.min.x + (length.x / 2.0f)};
    } else if (length.y >= length.x && length.y >= length.z) {
        return {Axis::Y, bounds.min.y + (length.y / 2.0f)};
    } else {
        return {Axis::Z, bounds.min.z + (length.z / 2.0f)};
    }
}

crayg::BoundingBox computeBounds(const std::vector<crayg::SceneObject *> &objects) {
    if (objects.empty()) {
        return {};
    }
    auto boundingBox = objects[0]->getBounds();
    for (const auto &obj: objects) {
        boundingBox = boundingBox.unionWith(obj->getBounds());
    }
    return boundingBox;
}

crayg::BoundingBox computeCentroidBounds(const std::vector<crayg::SceneObject *> &objects) {// todo this is wrong i think
    if (objects.empty()) {
        return {};
    }
    crayg::BoundingBox boundingBox(objects[0]->getBounds().getCentroid(), objects[0]->getBounds().getCentroid());
    for (const auto &obj: objects) {
        const crayg::BoundingBox objectBounds = obj->getBounds();
        if (objectBounds.min.x < boundingBox.min.x) {
            boundingBox.min.x = objectBounds.min.x;
        }
        if (objectBounds.min.y < boundingBox.min.y) {
            boundingBox.min.y = objectBounds.min.y;
        }
        if (objectBounds.min.z < boundingBox.min.z) {
            boundingBox.min.z = objectBounds.min.z;
        }

        if (objectBounds.max.x > boundingBox.max.x) {
            boundingBox.max.x = objectBounds.max.x;
        }
        if (objectBounds.max.y > boundingBox.max.y) {
            boundingBox.max.y = objectBounds.max.y;
        }
        if (objectBounds.max.z > boundingBox.max.z) {
            boundingBox.max.z = objectBounds.max.z;
        }
    }
    return boundingBox;
}
bool isLeft(const crayg::SceneObject *obj, const SplitInfo &splitInfo) {
    if (splitInfo.axis == Axis::X) {
        return obj->getBounds().getCentroid().x < splitInfo.splitPoint;
    } else if (splitInfo.axis == Axis::Y) {
        return obj->getBounds().getCentroid().y < splitInfo.splitPoint;
    } else {
        return obj->getBounds().getCentroid().z < splitInfo.splitPoint;
    }
}

crayg::BvhNode *buildTree(const std::vector<SceneObject *> &objects) {
    const auto bounds = computeBounds(objects);
    std::vector<crayg::SceneObject *> left, right;
    const crayg::BoundingBox centroidBounds = computeCentroidBounds(objects);
    const SplitInfo splitInfo = getSplitInfo(centroidBounds);
    for (const auto &obj: objects) {
        if (isLeft(obj, splitInfo)) {
            left.push_back(obj);
        } else {
            right.push_back(obj);
        }
    }
    if (objects.size() == left.size() || objects.size() == right.size()) {
        return new BvhNode(bounds, nullptr, nullptr, objects);
    }

    return new BvhNode(bounds,
                       !left.empty() ? buildTree(left) : nullptr,
                       !right.empty() ? buildTree(right) : nullptr,
                       std::vector<crayg::SceneObject *>());
}

crayg::BvhNode *BvhBuilder::build() const {
    std::vector<crayg::SceneObject *> objects;
    for (auto &obj: scene.objects) {
        objects.push_back(obj.get());
    }
    return buildTree(objects);
}
BvhBuilder::BvhBuilder(const Scene &scene) : scene(scene) {}
}
