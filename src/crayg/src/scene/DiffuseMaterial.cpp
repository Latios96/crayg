#include "DiffuseMaterial.h"

namespace crayg {

DiffuseMaterial::DiffuseMaterial(const Color &diffuseColor) : diffuseColor(diffuseColor) {}

DiffuseMaterial::DiffuseMaterial(const std::string &name, const Color &diffuseColor)
    : Material(name), diffuseColor(diffuseColor) {

}

Color DiffuseMaterial::getDiffuseColor() {
    return diffuseColor;
}

DiffuseMaterial::DiffuseMaterial() : Material() {

}
Color DiffuseMaterial::evaluate(const SurfaceInteraction &surfaceInteraction) {
    return diffuseColor;
}
std::string DiffuseMaterial::getType() {
    return "DiffuseMaterial";
}

}
