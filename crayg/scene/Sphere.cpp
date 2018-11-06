//
// Created by jan on 19.08.18.
//

#include "Sphere.h"

Ray Sphere::intersect(Ray ray) {
    ray.startPoint = ray.startPoint + getPosition().invert();

    float b = 2.0f * (ray.startPoint.x * ray.direction.x +
                      ray.startPoint.y * ray.direction.y +
                      ray.startPoint.z * ray.direction.z);

    float c = ray.startPoint.x * ray.startPoint.x +
              ray.startPoint.y * ray.startPoint.y +
              ray.startPoint.z * ray.startPoint.z - radius * radius;

    float d = b*b - (4.0f * c);

    const bool noIntersection = d < 0.0f;
    const bool isTangent = d == 0;

    if(noIntersection){
        return {Vector3f(), Vector3f(), std::numeric_limits<float>::max()};
    }
    else if(isTangent){
        // only one solution, calculate t
        const float t0 = (float) (b * (-1.0) / 2.0);
        return {ray.startPoint - getPosition().invert(), ray.direction, t0};
    }
    else{
        const double sqrtD = sqrt(d);

        const float t0 = (float) ((b *-1.0 - sqrtD) / 2.0);

        // if t0 > 0 its the point we want to render
        if(t0>0){
            return {ray.startPoint - getPosition().invert(), ray.direction, t0};
        }
        else{
            return {Vector3f(), Vector3f(), std::numeric_limits<float>::max()};
        }
    }
}

bool Sphere::intersects(Ray ray) {

    ray.startPoint = ray.startPoint + getPosition().invert();

    float b = 2.0f * (ray.startPoint.x * ray.direction.x +
            ray.startPoint.y * ray.direction.y +
            ray.startPoint.z * ray.direction.z);

    float c = ray.startPoint.x * ray.startPoint.x +
            ray.startPoint.y * ray.startPoint.y +
            ray.startPoint.z * ray.startPoint.z - radius * radius;

    float d = b*b - (4.0f * c);

    return d >= 0.0f;
}

Sphere::Sphere(Vector3f position, float radius) : SceneObject(position), radius(radius) {}

float Sphere::getRadius() const {
    return radius;
}

Sphere::~Sphere() {

}

void Sphere::serialize(Serializer &serializer) {
    SceneObject::serialize(serializer);
    serializer.writeType("Sphere");
    serializer.writeFloat("radius", radius);
}

void Sphere::deserialize(Deserializer &deserializer) {
    SceneObject::deserialize(deserializer);
    radius = deserializer.readFloat("radius");
}

Sphere::Sphere() {
    radius = 0;
}


void SceneObject::serialize(Serializer &serializer) {
    serializer.writeVector3f("position", this->getPosition());
}

SceneObject::SceneObject(Vector3f position) : Transformable(position) {

}

void SceneObject::deserialize(Deserializer &deserializer) {
    setPosition(deserializer.readVector3f("position"));
}

SceneObject::SceneObject() = default;
