//
// Created by Jan Honsbrok on 09.10.18.
//

#ifndef CRAYG_ATTRIBUTEIMPL_H
#define CRAYG_ATTRIBUTEIMPL_H

#include "string"
#include <iostream>

class GenericAttributeImpl {
public:
    std::string attr_type;
    bool isInt(){
        return attr_type == "int";
    }
    bool isFloat(){
        return attr_type == "float";
    }
    bool isVector3f(){
        return attr_type == "Vector3f";
    }
    bool isString(){
        return attr_type == "String";
    }

    virtual ~GenericAttributeImpl() = default;

};

template<typename T>
class AttributeImpl : public GenericAttributeImpl {
public:
    T value;

    ~AttributeImpl() override = default;
};
#endif //CRAYG_ATTRIBUTEIMPL_H
