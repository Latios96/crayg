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
void SceneObject::getPrimitives(std::vector<Imageable *> &target, bool *isOwning) {
    target.push_back(this);
    *isOwning = false;
}

SceneObject::SceneObject() = default;

}