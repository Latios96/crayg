#include "RectLight.h"
#include "intersectors/SceneIntersector.h"
#include "Logger.h"

namespace crayg {

RectLight::RectLight() = default;
RectLight::RectLight(const Transform &transform, float intensity, float width, float height) : AreaLight(transform,
                                                                                                         intensity),
                                                                                               width(width),
                                                                                               height(height) {}

Vector3f RectLight::sampleLightShape() const {
    float positionByWidth = Random::random() * width - width / 2;
    float positionByHeight = Random::random() * height - height / 2;
    Vector3f positionOnPlane = {positionByWidth, positionByHeight, 0};
    const Vector3f samplePosition = getTransform().apply(positionOnPlane);
    return samplePosition;
}
std::string RectLight::getType() {
    return "RectLight";
}
Vector3f RectLight::getNormal(Vector3f point) {
    return transform.applyForNormal({0, 0, 1});
}

Imageable::Intersection RectLight::intersect(Ray ray) {
  const Vector3f normal = getNormal({0, 0, 0}).normalize();
  const Vector3f center = transform.apply({0, 0, 0});
  float D = normal.dot(center);
  float t = -normal.dot(ray.startPoint) + D / normal.dot(ray.direction);
  if (t <= 0) {
    return Imageable::Intersection::createInvalid();
  }
  const Vector3f pointOnPlane = ray.constructIntersectionPoint(t);
  const float distanceToCenter = (pointOnPlane - center).lengthSquared();
  const bool isIntersecting = distanceToCenter <= (pow(width, 2));
  if (isIntersecting) {
    return Imageable::Intersection(t, shared_from_this());
  }
  return Imageable::Intersection::createInvalid();
}
bool RectLight::isIntersecting(Ray ray) {
  const Vector3f normal = getNormal({0, 0, 0});
  const Vector3f center = transform.apply({0, 0, 0});
  float D = normal.dot(center);
  float t = -normal.dot(ray.startPoint) + D / normal.dot(ray.direction);
  if (t <= 0) {
    return false;
  }
  const Vector3f pointOnPlane = ray.constructIntersectionPoint(t);
  const float distanceToCenter = (pointOnPlane - center).lengthSquared();
  return distanceToCenter <= (pow(width, 2));
}
BoundingBox RectLight::getBounds() const {
    return BoundingBox::fromCenterAndRadius(getPosition(), width);
}
float RectLight::getWidth() const {
    return width;
}
void RectLight::setWidth(float width) {
    RectLight::width = width;
}
float RectLight::getHeight() const {
    return height;
}
void RectLight::setHeight(float height) {
    RectLight::height = height;
}
float RectLight::area() const {
    const Vector3f widthVector = getPosition() - getTransform().apply({width / 2, 0, 0});
    const Vector3f heightVector = getPosition() - getTransform().apply({0, height / 2, 0});
    const float area = widthVector.length() * 2 * heightVector.length() * 2;
    return area;
}

}