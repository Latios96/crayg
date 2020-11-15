//
// Created by Jan on 15.11.2020.
//

#include "DiffuseMaterial.h"

DiffuseMaterial::DiffuseMaterial(const Color &diffuseColor) : diffuseColor(diffuseColor) {}

Color DiffuseMaterial::getDiffuseColor() {
    return diffuseColor;
}
void DiffuseMaterial::serialize(Serializer &serializer) {
    ShadingNode::serialize(serializer);
    serializer.writeType("DiffuseMaterial");
    serializer.writeColor("diffuseColor", diffuseColor);
}
void DiffuseMaterial::deserialize(Deserializer &deserializer) {

}

void DiffuseMaterial::connectOutputToInput(const std::string &inputPlugName, PlugPtr outputPlug) {

}
PlugPtr DiffuseMaterial::getPlugByName(const std::string &inputPlugName) {
    return {};
}
