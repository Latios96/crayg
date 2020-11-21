//
// Created by Jan on 17.11.2020.
//

#include "ReflectiveMaterial.h"

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
void ReflectiveMaterial::serialize(Serializer &serializer) {
    ShadingNode::serialize(serializer);
    serializer.writeType("ReflectiveMaterial");
}
void ReflectiveMaterial::deserialize(Deserializer &deserializer) {
    ShadingNode::deserialize(deserializer);
}
bool ReflectiveMaterial::isEmissive() {
    return false;
}
