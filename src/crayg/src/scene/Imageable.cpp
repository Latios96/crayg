//
// Created by Jan Honsbrok on 25.11.18.
//

#include "Imageable.h"

#include <utility>

namespace crayg {

Imageable::Intersection::Intersection(float rayParameter, std::shared_ptr<Imageable> imageable) : rayParameter(
    rayParameter),
                                                                                                  imageable(std::move(
                                                                                                      imageable)) {}
std::shared_ptr<Material> Imageable::getMaterial() const {
    return material;
}
void Imageable::setMaterial(const std::shared_ptr<Material> &material) {
    Imageable::material = material;
}

}