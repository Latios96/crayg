//
// Created by Jan Honsbrok on 07.11.18.
//

#include "SceneObject.h"

void SceneObject::serialize(Serializer &serializer) {
    serializer.writeMatrix4x4f("transform", this->getTransform().matrix);
    if (material) {
        serializer.writeString("material", material->getName());
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
std::shared_ptr<Material> SceneObject::getMaterial() const {
    return material;
}
void SceneObject::setMaterial(const std::shared_ptr<Material> &material) {
    SceneObject::material = material;
}

SceneObject::SceneObject() = default;
