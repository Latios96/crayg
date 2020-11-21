//
// Created by Jan on 21.11.2020.
//

#define _USE_MATH_DEFINES
#include <cmath>
#include "DiskLight.h"
#include "intersectors/SceneIntersector.h"

void DiskLight::serialize(Serializer &serializer) {
    Light::serialize(serializer);
    serializer.writeFloat("radius", radius);
}
void DiskLight::deserialize(Deserializer &deserializer) {
    Light::deserialize(deserializer);
    radius = deserializer.readFloat("radius");
}
float DiskLight::calculateShadowFactor(SceneIntersector &sceneIntersector, const Vector3f &point) {
    //float r = radius * sqrt((double(rand()) / RAND_MAX));
    float r = radius * (double(rand()) / RAND_MAX);
    float theta = (double(rand()) / RAND_MAX) * 2 * M_PI;
    Vector3f positionOnPlane = {r * cos(theta), r * sin(theta), 0};
    const Vector3f transformedPosition = getTransform().apply(positionOnPlane);

    const Vector3f shadowVector = (transformedPosition - point).normalize();
    const Vector3f normal = getNormal({0, 0, 0});
    if (normal.scalarProduct(shadowVector.normalize()) > 0) {
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
DiskLight::DiskLight(const Transform &transform, float intensity, float radius) : Light(transform, intensity),
                                                                                  radius(radius) {

}
float DiskLight::getRadius() const {
    return radius;
}
DiskLight::DiskLight() = default;


