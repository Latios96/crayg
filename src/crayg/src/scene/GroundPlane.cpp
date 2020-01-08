//
// Created by Jan Honsbrok on 07.11.18.
//

#include "GroundPlane.h"

void GroundPlane::serialize(Serializer &serializer) {
    SceneObject::serialize(serializer);
    serializer.writeType("GroundPlane");
}

void GroundPlane::deserialize(Deserializer &deserializer) {
    SceneObject::deserialize(deserializer);
}

bool GroundPlane::isIntersecting(Ray ray) {
    auto scalar = normal.scalarProduct(ray.direction);
    return scalar != 0;
}

Vector3f GroundPlane::getNormal(Vector3f point) {
    return normal;
}

Imageable::Intersection GroundPlane::intersect(Ray ray) {
    const float scalar = normal.scalarProduct(ray.direction);

    if (scalar == 0) {
        return Imageable::Intersection::createInvalid();
    } else {
        const float t = -(normal.scalarProduct(ray.startPoint) + getPosition().length()) / scalar;

        if (t > 0) {
            return {t, shared_from_this()};
        }
        return Imageable::Intersection::createInvalid();
    }
}
