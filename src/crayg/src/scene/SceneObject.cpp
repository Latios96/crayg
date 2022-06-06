//
// Created by Jan Honsbrok on 07.11.18.
//

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

SceneObject::SceneObject() = default;

}