//
// Created by Jan on 21.11.2020.
//

#include "EmissiveMaterial.h"

namespace crayg {

Color EmissiveMaterial::getDiffuseColor() {
    return {10, 10, 10};
}
float EmissiveMaterial::reflectivity() {
    return 0;
}
void EmissiveMaterial::connectOutputToInput(const std::string &inputPlugName, PlugPtr outputPlug) {

}
PlugPtr EmissiveMaterial::getPlugByName(const std::string &inputPlugName) {
    return PlugPtr();
}
bool EmissiveMaterial::isEmissive() {
    return true;
}

}
