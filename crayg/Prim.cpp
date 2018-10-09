//
// Created by Jan Honsbrok on 09.10.18.
//

#include "Prim.h"

Prim Prim::definePrim(const std::string &path, Stage &stage) {
    auto primMap = stage.createPrimMap(path);
    return {primMap};
}

TestPrim TestPrim::defineTestPrim(const std::string &path, Stage &stage) {
    auto primMap =  stage.createPrimMap(path);
    AttributeImpl<int> *intAttributeImpl = stage.createIntAttributeImpl();
    primMap->insert(std::make_pair("size", intAttributeImpl));

    return TestPrim(primMap);
}

TestPrim::TestPrim(std::map<std::string, GenericAttributeImpl *> *primMap) : Prim(primMap) {}


