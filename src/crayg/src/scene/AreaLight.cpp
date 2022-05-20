//
// Created by Jan on 20.11.2020.
//
#define _USE_MATH_DEFINES
#include <cmath>
#include "AreaLight.h"
#include "intersectors/SceneIntersector.h"

namespace crayg {

float AreaLight::calculateShadowFactor(SceneIntersector &sceneIntersector, const Vector3f &point) {
    float r = width * sqrt((double(rand()) / RAND_MAX));
    float theta = (double(rand()) / RAND_MAX) * 2 * M_PI;
    Vector3f positionOnPlane = {r * cos(theta), r * sin(theta), 0};
    const Vector3f transformedPosition = getTransform().apply(positionOnPlane);

    const Vector3f shadowVector = (transformedPosition - point).normalize();
    if (getNormal({0, 0, 0}).scalarProduct(shadowVector) > 0) {
        return Light::FULL_SHADOW;
    }
    Ray shadowRay(point, shadowVector);
    const Imageable::Intersection intersection = sceneIntersector.intersect(shadowRay);

    const bool hasIntersection = intersection.imageable != nullptr;
    if (hasIntersection) {
        const bool intersectionIsBehindLight = shadowVector.length() <= intersection.rayParameter;
        if (intersectionIsBehindLight) {
            return Light::NO_SHADOW;
        } else {
            return Light::FULL_SHADOW;
        }
    } else {
        return Light::NO_SHADOW;
    }
}
void AreaLight::serialize(Serializer &serializer) {
    Light::serialize(serializer);
    serializer.writeType("AreaLight");
    serializer.writeFloat("width", width);
    serializer.writeFloat("height", height);
}
void AreaLight::deserialize(Deserializer &deserializer) {
    Light::deserialize(deserializer);
    width = deserializer.readFloat("width");
    height = deserializer.readFloat("height");
}
std::string AreaLight::getType() {
    return "AreaLight";
}
Vector3f AreaLight::getNormal(Vector3f point) {
    return transform.apply({1, 0, 0});
}

Imageable::Intersection AreaLight::intersect(Ray ray) {
    const Vector3f normal = getNormal({0, 0, 0}).normalize();
    const Vector3f center = transform.apply({0, 0, 0});
    float D = normal.scalarProduct(center);
    float t = -normal.scalarProduct(ray.startPoint) + D / normal.scalarProduct(ray.direction);
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
bool AreaLight::isIntersecting(Ray ray) {
    const Vector3f normal = getNormal({0, 0, 0});
    const Vector3f center = transform.apply({0, 0, 0});
    float D = normal.scalarProduct(center);
    float t = -normal.scalarProduct(ray.startPoint) + D / normal.scalarProduct(ray.direction);
    if (t <= 0) {
        return false;
    }
    const Vector3f pointOnPlane = ray.constructIntersectionPoint(t);
    const float distanceToCenter = (pointOnPlane - center).lengthSquared();
    return distanceToCenter <= (pow(width, 2));
}
BoundingBox AreaLight::getBounds() const {
    return BoundingBox::fromCenterAndRadius(getPosition(), width);
}
float AreaLight::getWidth() const {
    return width;
}
void AreaLight::setWidth(float width) {
    AreaLight::width = width;
}
float AreaLight::getHeight() const {
    return height;
}
void AreaLight::setHeight(float height) {
    AreaLight::height = height;
}

}