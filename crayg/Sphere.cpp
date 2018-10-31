//
// Created by jan on 19.08.18.
//

#include "Sphere.h"

Vector3f Sphere::intersect(Ray ray) {
    return Vector3f();
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


void SceneObject::serialize(Serializer &serializer) {
    serializer.writeVector3f("position", this->getPosition());
}

SceneObject::SceneObject(Vector3f position) : Transformable(position) {

}

SceneObject::SceneObject() = default;
