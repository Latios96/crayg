//
// Created by Jan Honsbrok on 09.10.18.
//

#ifndef CRAYG_PRIM_H
#define CRAYG_PRIM_H


#include <string>
#include <map>
#include "Stage.h"
#include "Attribute.h"

class Prim {
public:

    static Prim definePrim(const std::string& path, Stage& stage);

    // todo get attributes


protected:
    Prim(std::map<std::string, GenericAttributeImpl*> *primMap) : primMap(primMap) {}
    std::map<std::string, GenericAttributeImpl*>* primMap;

    template <typename T>
    Attribute<T> getAsAttribute(const std::string &attributeName);

    /*void defineIntAttribute(const std::string &attributeName, Stage &stage);*/
    template <typename T>
    void defineAttribute(const std::string &attributeName, Stage &stage);

    void definePrimAttributes(Stage &stage);
};

template<typename T>
void Prim::defineAttribute(const std::string &attributeName, Stage &stage) {
    AttributeImpl<T> *intAttributeImpl = stage.createAttributeImpl<T>();
    primMap->insert(std::make_pair(attributeName, intAttributeImpl));
}


template<typename T>
Attribute<T> Prim::getAsAttribute(const std::string &attributeName) {
    return {static_cast<AttributeImpl<T>*>(primMap->at(attributeName))};
}

#endif //CRAYG_PRIM_H
