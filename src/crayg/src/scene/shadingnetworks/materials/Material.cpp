#include "Material.h"
#include "basics/Ray.h"
#include "basics/Vector3f.h"

namespace crayg {

Material::Material(const std::string &name) : ShadingNode(name) {
}

Material::Material() : ShadingNode() {
}

void Material::getLobes(const SurfaceInteraction &surfaceInteraction, Lobes &lobes) {
    lobes.specular.weight = Color::createBlack();
    lobes.diffuse.weight = Color::createBlack();
}
}