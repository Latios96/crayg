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

    Attribute<int> getAsIntAttribute(const std::string &attributeName){
        return {static_cast<AttributeImpl<int>*>(primMap->at(attributeName))};
    }

    void defineIntAttribute(const std::string &attributeName, Stage &stage);
};



#endif //CRAYG_PRIM_H
