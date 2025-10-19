#include "Material.h"
#include "crayg/foundation/math/geometry/Ray.h"
#include "crayg/foundation/math/geometry/Vector3f.h"

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