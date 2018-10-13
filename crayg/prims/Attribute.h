//
// Created by Jan Honsbrok on 09.10.18.
//

#ifndef CRAYG_ATTRIBUTE_H
#define CRAYG_ATTRIBUTE_H

#include "AttributeImpl.h"

template<typename T>
class Attribute {
public:
    void setValue(T value);

    T& getValue();

    Attribute(AttributeImpl<T>* attributeImpl){
        this->attributeImpl = attributeImpl;
    }

private:
    AttributeImpl<T>* attributeImpl;
};

template<typename T>
void Attribute<T>::setValue(T value) {
    attributeImpl->value = value;
}

template<typename T>
T &Attribute<T>::getValue() {
    return attributeImpl->value;
}

#endif //CRAYG_ATTRIBUTE_H
