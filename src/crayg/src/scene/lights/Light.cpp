#include "Light.h"
#include "scene/shadingnetworks/materials/EmissiveMaterial.h"

namespace crayg {

float Light::getIntensity() const {
    return intensity;
}

void Light::setIntensity(float intensity) {
    Light::intensity = intensity;
    std::dynamic_pointer_cast<EmissiveMaterial>(getMaterial())->emission = color * intensity;
}

Light::Radiance Light::radiance(const Vector3f &point, const Vector3f &normal) {
    const Vector3f shadowVector = getPosition() - point;
    Ray shadowRay(point, shadowVector);

    return {color * intensity / shadowVector.lengthSquared() * normal.dot(shadowVector), shadowRay};
}

std::string Light::getType() {
    return "Light";
}

Vector3f Light::getNormal(Vector3f point) {
    return Vector3f();
}

Imageable::Intersection Light::intersect(Ray ray) {
    return Imageable::Intersection::createInvalid();
}

bool Light::isIntersecting(Ray ray) {
    return false;
}

Light::Light() {
    setMaterial(std::make_shared<EmissiveMaterial>());
    imageableType = ImageableType::LIGHT;
}

Light::Light(const Transform &transform, float intensity) : Transformable(transform) {
    setMaterial(std::make_shared<EmissiveMaterial>());
    setIntensity(intensity);
    imageableType = ImageableType::LIGHT;
}

BoundingBox Light::getBounds() const {
    return BoundingBox();
}

const std::string &Light::getName() const {
    return name;
}

void Light::setName(const std::string &name) {
    Light::name = name;
}

Light::Radiance::Radiance(const Color &radiance, const Ray &ray) : radiance(radiance), ray(ray) {
}

bool Light::Radiance::operator==(const Light::Radiance &rhs) const {
    return radiance == rhs.radiance && ray == rhs.ray;
}

bool Light::Radiance::operator!=(const Light::Radiance &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Light::Radiance &radiance) {
    os << ToStringHelper("Radiance").addMember("radiance", radiance.radiance).addMember("ray", radiance.ray).finish();
    return os;
}

const Color &Light::getColor() const {
    return color;
}

void Light::setColor(const Color &color) {
    Light::color = color;
    std::dynamic_pointer_cast<EmissiveMaterial>(getMaterial())->emission = color * intensity;
}
}
