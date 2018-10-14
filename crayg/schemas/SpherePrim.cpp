//
// Created by Jan Honsbrok on 13.10.18.
//

#include "SpherePrim.h"

SpherePrim::SpherePrim(std::map<std::string, GenericAttributeImpl *> *primMap) : TransformablePrim(primMap) {

}

void SpherePrim::defineSphereAttributes(Stage &stage) {
    defineAttribute<int>("size", stage);
}

