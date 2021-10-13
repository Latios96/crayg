//
// Created by Jan Honsbrok on 02.01.20.
//

#include "PointCloud.h"
#include "Sphere.h"

namespace crayg {

bool PointCloud::isIntersecting(Ray ray) {
    auto sphere = std::make_shared<Sphere>();
    for (unsigned long i = 0; i < points.size(); i++) {
        sphere->setPosition(transform.apply(points[i]));
        sphere->setRadius(radii[i]);
        if (sphere->isIntersecting(ray)) {
            return true;
        }
    }
    return false;
}
Vector3f PointCloud::getNormal(Vector3f point) {
    return {};
}
Imageable::Intersection PointCloud::intersect(Ray ray) {
    auto sphere = std::make_shared<Sphere>();
    for (unsigned long i = 0; i < points.size(); i++) {
        sphere->setPosition(transform.apply(points[i]));
        sphere->setRadius(radii[i]);
        sphere->setMaterial(getMaterial());
        Intersection intersection = sphere->intersect(ray);
        if (intersection.isValid()) {
            return intersection;
        }
    }
    return Intersection::createInvalid();
}
void PointCloud::serialize(Serializer &serializer) {
    SceneObject::serialize(serializer);
    serializer.writeType("PointCloud");
    serializer.writeVector3fArray("points", points);
    serializer.writeFloatArray("radii", radii);
}
void PointCloud::deserialize(Deserializer &deserializer) {
    SceneObject::deserialize(deserializer);
    deserializer.readVector3fArray("points", points);
    deserializer.readFloatArray("radii", radii);
}
const std::vector<Vector3f> &PointCloud::getPoints() const {
    return points;
}
void PointCloud::setPoints(const std::vector<Vector3f> &points) {
    PointCloud::points = points;
}
const std::vector<float> &PointCloud::getRadii() const {
    return radii;
}
void PointCloud::setRadii(const std::vector<float> &radii) {
    PointCloud::radii = radii;
}
BoundingBox PointCloud::getBounds() const {
    BoundingBox boundingBox = BoundingBox::fromCenterAndRadius(points[0], radii[0]);
    for (unsigned long i = 0; i < points.size(); i++) {
        boundingBox = boundingBox.unionWith(BoundingBox::fromCenterAndRadius(points[i], radii[i]));
    }
    return boundingBox;
}

}
