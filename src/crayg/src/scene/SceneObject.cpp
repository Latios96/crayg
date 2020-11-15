//
// Created by Jan Honsbrok on 07.11.18.
//

#include "SceneObject.h"

void SceneObject::serialize(Serializer &serializer) {
    serializer.writeMatrix4x4f("transform", this->getTransform().matrix);
    if (getMaterial()) {
        serializer.writeString("material", getMaterial()->getName());
    }
}

SceneObject::SceneObject(Vector3f position) : Transformable(position) {

}

void SceneObject::deserialize(Deserializer &deserializer) {
    if (deserializer.hasProperty("position")) {
        setPosition(deserializer.readVector3f("position"));
        return;
    }
    transform = Transform(deserializer.readMatrix4x4f("transform"));
}

SceneObject::SceneObject() = default;
