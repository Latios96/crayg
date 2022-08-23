#include "DiffuseMaterial.h"

namespace crayg {

DiffuseMaterial::DiffuseMaterial(const Color &diffuseColor) : diffuseColor(diffuseColor) {}

DiffuseMaterial::DiffuseMaterial(const std::string &name, const Color &diffuseColor)
    : Material(name), diffuseColor(diffuseColor) {

}

Color DiffuseMaterial::getDiffuseColor() {
    return diffuseColor;
}

void DiffuseMaterial::connectOutputToInput(const std::string &inputPlugName, PlugPtr outputPlug) {

}
PlugPtr DiffuseMaterial::getPlugByName(const std::string &inputPlugName) {
    return {};
}
DiffuseMaterial::DiffuseMaterial() : Material() {

}
Color DiffuseMaterial::evaluate(const SurfaceInteraction &surfaceInteraction) {
  return diffuseColor;
}

}
