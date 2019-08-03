//
// Created by Jan Honsbrok on 07.11.18.
//

#include "SceneObject.h"

void SceneObject::serialize(Serializer &serializer) {
    serializer.writeVector3f("position", this->getPosition());
}

SceneObject::SceneObject(Vector3f position) : Transformable(position) {

}

void SceneObject::deserialize(Deserializer &deserializer) {
    setPosition(deserializer.readVector3f("position"));
}

SceneObject::SceneObject() = default;
