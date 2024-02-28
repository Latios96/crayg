#include "Material.h"
#include "basics/Ray.h"
#include "basics/Vector3f.h"

namespace crayg {

Material::Material(const std::string &name) : ShadingNode(name) {
}

Material::Material() : ShadingNode() {
}

}