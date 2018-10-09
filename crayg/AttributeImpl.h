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
};

template<typename T>
class AttributeImpl : public GenericAttributeImpl {
public:
    T value;
};
#endif //CRAYG_ATTRIBUTEIMPL_H
