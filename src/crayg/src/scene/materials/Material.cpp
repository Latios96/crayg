#include "Material.h"
#include "basics/Ray.h"
#include "basics/Vector3f.h"

namespace crayg {

Material::Material(const std::string &name) : ShadingNode(name) {
}

Material::Material() : ShadingNode() {
}

void Material::connectOutputToInput(const std::string &inputPlugName, PlugPtr outputPlug) {
}

PlugPtr Material::getPlugByName(const std::string &inputPlugName) {
    return PlugPtr();
}

}