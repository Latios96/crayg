#include "SceneObject.h"

namespace crayg {

SceneObject::SceneObject(Vector3f position) : Transformable(position) {
}

const std::string &SceneObject::getName() const {
    return name;
}

void SceneObject::setName(const std::string &name) {
    SceneObject::name = name;
}

void SceneObject::getPrimitives(std::vector<Imageable *> &target) const {
    target.push_back(const_cast<SceneObject *>(this));
}

std::size_t SceneObject::primitiveCount() const {
    return 1;
}

SceneObject::SceneObject() = default;

}