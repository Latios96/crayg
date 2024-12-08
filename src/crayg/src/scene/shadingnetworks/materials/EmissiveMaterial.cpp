#include "EmissiveMaterial.h"

namespace crayg {
EmissiveMaterial::EmissiveMaterial() {
}

EmissiveMaterial::EmissiveMaterial(const Color &emission) : emission(emission) {
}

EmissiveMaterial::EmissiveMaterial(const std::string &name) : Material(name) {
}

EmissiveMaterial::EmissiveMaterial(const std::string &name, const Color &emission)
    : Material(name), emission(emission) {
}

void EmissiveMaterial::getLobes(const SurfaceInteraction &surfaceInteraction, Lobes &lobes) {
    lobes.emission.weight = emission;
}

std::string EmissiveMaterial::getType() const {
    return "EmissiveMaterial";
}

ShadingNodeOutputType EmissiveMaterial::getOutputType() {
    return ShadingNodeOutputType::COLOR;
}
} // crayg