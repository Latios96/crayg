//
// Created by Jan Honsbrok on 13.10.18.
//

#include <foundation/Vector3f.h>
#include "TransformablePrim.h"

TransformablePrim::TransformablePrim(std::map<std::string, GenericAttributeImpl *> *primMap) : ImageablePrim(primMap) {

}

void TransformablePrim::defineTransformableAttributes(Stage &stage) {
    defineAttribute<Vector3f>("position", stage);
}
