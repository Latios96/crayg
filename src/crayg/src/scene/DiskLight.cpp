#include <boost/math/constants/constants.hpp>
#include "DiskLight.h"
#include "intersectors/SceneIntersector.h"

namespace crayg {

Vector3f DiskLight::sampleLightShape() const {
    float r = radius * sqrt((double(rand()) / RAND_MAX));
    float theta = (double(rand()) / RAND_MAX) * 2 * boost::math::constants::pi<double>();
    Vector3f positionOnPlane = {r * cos(theta), r * sin(theta), 0};
    return getTransform().apply(positionOnPlane);
}
Vector3f DiskLight::getNormal(Vector3f point) {
    return transform.applyForNormal({1, 0, 0}).normalize();
}
Imageable::Intersection DiskLight::intersect(Ray ray) {
    const Vector3f normal = getNormal({0, 0, 0}).normalize();
    const Vector3f center = transform.apply({0, 0, 0});
    if (normal.scalarProduct(ray.direction) > 0) {
        return Imageable::Intersection::createInvalid();
    }
    float D = normal.scalarProduct(center);
    float t = -normal.scalarProduct(ray.startPoint) + D / normal.scalarProduct(ray.direction);
    if (t <= 0) {
        return Imageable::Intersection::createInvalid();
    }
    const Vector3f pointOnPlane = ray.constructIntersectionPoint(t);
    const float distanceToCenter = (pointOnPlane - center).lengthSquared();
    const bool isIntersecting = distanceToCenter <= (pow(radius, 2));
    if (isIntersecting) {
        return Imageable::Intersection(t, shared_from_this());
    }
    return Imageable::Intersection::createInvalid();
}
bool DiskLight::isIntersecting(Ray ray) {
    const Vector3f normal = getNormal({0, 0, 0});
    const Vector3f center = transform.apply({0, 0, 0});
    if (normal.scalarProduct(ray.direction) > 0) {
        return false;
    }
    float D = normal.scalarProduct(center);
    float t = -normal.scalarProduct(ray.startPoint) + D / normal.scalarProduct(ray.direction);
    if (t <= 0) {
        return false;
    }
    const Vector3f pointOnPlane = ray.constructIntersectionPoint(t);
    const float distanceToCenter = (pointOnPlane - center).lengthSquared();
    return distanceToCenter <= (pow(radius, 2));
}
std::string DiskLight::getType() {
    return "DiskLight";
}
DiskLight::DiskLight(const Transform &transform, float intensity, float radius) : AreaLight(transform, intensity),
                                                                                  radius(radius) {

}
float DiskLight::getRadius() const {
    return radius;
}
BoundingBox DiskLight::getBounds() const {
    return BoundingBox::fromCenterAndRadius(getPosition(), radius);
}
void DiskLight::setRadius(float radius) {
    DiskLight::radius = radius;
}
DiskLight::DiskLight() = default;

}

