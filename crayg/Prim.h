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
};

class TestPrim : Prim{
public:
    static TestPrim defineTestPrim(const std::string& path, Stage& stage);

    TestPrim(std::map<std::string, GenericAttributeImpl *> *primMap);

    Attribute<int> getSizeAttribute(){
        return Attribute<int>(static_cast<AttributeImpl<int>*>(primMap->at("size")));
    }
private:
    //GenericAttributeImpl* sizeAttributeImpl;
};

#endif //CRAYG_PRIM_H
