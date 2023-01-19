#include <algorithm>
#include "NaiveBvhSceneIntersector.h"

namespace crayg {

bool isIntersectingTree(const Ray &ray, const NaiveBvhNode &node) {
    const bool intersects = node.boundingBox.isIntersecting(ray);
    if (!intersects) {
        return false;
    }
    if (node.isLeaf()) {
        return std::any_of(node.objects.begin(),
                           node.objects.end(),
                           [&ray](Imageable *intersectable) { return intersectable->isIntersecting(ray); });
    }
    if (node.left && isIntersectingTree(ray, *node.left)) {
        return true;
    }
    if (node.right && isIntersectingTree(ray, *node.right)) {
        return true;
    }
    return false;
}

Imageable::Intersection intersectTree(const Ray &ray, const NaiveBvhNode &node) {
    const bool intersects = node.boundingBox.isIntersecting(ray);
    if (!intersects) {
        return Imageable::Intersection::createInvalid();
    }
    if (node.isLeaf()) {
        Imageable::Intersection hitIntersection(std::numeric_limits<float>::max(), nullptr);
        for (const auto &intersectable: node.objects) {
            Imageable::Intersection intersection = intersectable->intersect(ray);
            hitIntersection = Imageable::Intersection::nearest(intersection, hitIntersection);
        }
        return hitIntersection;
    }
    auto leftIntersection = Imageable::Intersection::createInvalid();
    auto rightIntersection = Imageable::Intersection::createInvalid();
    if (node.left) {
        leftIntersection = intersectTree(ray, *node.left);
    }
    if (node.right) {
        rightIntersection = intersectTree(ray, *node.right);
    }
    if (leftIntersection.rayParameter < rightIntersection.rayParameter && leftIntersection.imageable) {
        return leftIntersection;
    }
    return rightIntersection;
}

Imageable::Intersection NaiveBvhSceneIntersector::intersect(const Ray &ray) const {
    return intersectTree(ray, *bvh->root);
}
bool NaiveBvhSceneIntersector::isIntersecting(const Ray &ray) const {
    return isIntersectingTree(ray, *bvh->root);
}

NaiveBvhSceneIntersector::NaiveBvhSceneIntersector(Scene &scene, std::unique_ptr<NaiveBvh> bvh)
    : SceneIntersector(scene), bvh(std::move(bvh)) {}

}

