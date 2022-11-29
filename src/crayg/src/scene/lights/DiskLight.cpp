#include <boost/math/constants/constants.hpp>
#include "DiskLight.h"
#include "intersectors/SceneIntersector.h"

namespace crayg {

Vector3f DiskLight::sampleLightShape() const {
    float r = radius * sqrt(Random::random());
    float theta = Random::random() * 2 * boost::math::constants::pi<double>();
    Vector3f positionOnPlane = {r * cos(theta), r * sin(theta), 0};
    return getTransform().apply(positionOnPlane);
}
Vector3f DiskLight::getNormal(Vector3f point) {
    return transform.applyForNormal({0, 0, 1}).normalize();
}
Imageable::Intersection DiskLight::intersect(Ray ray) {
    const Vector3f normal = transform.applyForNormal(getNormal({0, 0, 0}));
    const Vector3f center = transform.apply({0, 0, 0});
  if (normal.dot(ray.direction) > 0) {
    return Imageable::Intersection::createInvalid();
  }
  float D = normal.dot(center);
  float t = -normal.dot(ray.startPoint) + D / normal.dot(ray.direction);
  if (t <= 0) {
    return Imageable::Intersection::createInvalid();
  }
  const Vector3f pointOnPlane = ray.constructIntersectionPoint(t);
  const float distanceToCenter = (pointOnPlane - center).lengthSquared();
  const bool isIntersecting = distanceToCenter <= (pow(radius, 2));
  if (isIntersecting) {
    return Imageable::Intersection(t, this);
  }
  return Imageable::Intersection::createInvalid();
}
bool DiskLight::isIntersecting(Ray ray) {
    const Vector3f normal = transform.applyForNormal(getNormal({0, 0, 0}));
    const Vector3f center = transform.apply({0, 0, 0});
  if (normal.dot(ray.direction) > 0) {
    return false;
  }
  float D = normal.dot(center);
  float t = -normal.dot(ray.startPoint) + D / normal.dot(ray.direction);
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
float DiskLight::area() const {
    const Vector3f radiusVector = getPosition() - getTransform().apply({radius, 0, 0});
    const float area = boost::math::constants::pi<float>() * radiusVector.lengthSquared();
    return area;
}
DiskLight::DiskLight() = default;

}

