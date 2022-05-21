//
// Created by Jan on 20.11.2020.
//
#define _USE_MATH_DEFINES
#include <cmath>
#include "AreaLight.h"
#include "intersectors/SceneIntersector.h"

namespace crayg {

float AreaLight::calculateShadowFactor(SceneIntersector &sceneIntersector, const Vector3f &point) {
    const Vector3f samplePosition = sampleLightShape();

    const Vector3f shadowVector = (samplePosition - point);
    const Vector3f normal = getNormal({0, 0, 0});
    if (normal.scalarProduct(shadowVector) > 0) {
        return Light::FULL_SHADOW;
    }
    Ray shadowRay(point, shadowVector.normalize());
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
Vector3f AreaLight::sampleLightShape() const {
    float positionByWidth = ((float) rand() / (RAND_MAX)) * width - width / 2;
    float positionByHeight = ((float) rand() / (RAND_MAX)) * height - height / 2;
    Vector3f positionOnPlane = {positionByWidth, positionByHeight, 0};
    const Vector3f samplePosition = getTransform().apply(positionOnPlane);
    return samplePosition;
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
    return transform.applyForNormal({0, 0, 1});
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