//
// Created by Jan Honsbrok on 09.10.18.
//

#ifndef CRAYG_ATTRIBUTEIMPL_H
#define CRAYG_ATTRIBUTEIMPL_H

#include "string"

class GenericAttributeImpl {
public:
    std::string attr_type;
    bool isInt(){
        return attr_type == "int";
    }
    bool isVector3f(){
        return attr_type == "Vector3f";
    }

    // todo destructor needs to be virtual i think
};

template<typename T>
class AttributeImpl : public GenericAttributeImpl {
public:
    T value;
};
#endif //CRAYG_ATTRIBUTEIMPL_H
