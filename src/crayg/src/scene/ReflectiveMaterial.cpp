#include "ReflectiveMaterial.h"

namespace crayg {

Color ReflectiveMaterial::getDiffuseColor() {
    return {};
}
float ReflectiveMaterial::reflectivity() {
    return 1;
}
void ReflectiveMaterial::connectOutputToInput(const std::string &inputPlugName, PlugPtr outputPlug) {

}
PlugPtr ReflectiveMaterial::getPlugByName(const std::string &inputPlugName) {
    return {};
}
bool ReflectiveMaterial::isEmissive() { return false; }
Color ReflectiveMaterial::evaluate(
    const SurfaceInteraction &surfaceInteraction) {
  return Color();
}

}