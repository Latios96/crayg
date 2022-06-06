//
// Created by Jan on 15.11.2020.
//

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
float DiffuseMaterial::reflectivity() {
    return 0;
}
bool DiffuseMaterial::isEmissive() {
    return false;
}

}
