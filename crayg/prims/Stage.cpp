//
// Created by Jan Honsbrok on 09.10.18.
//

#include <iostream>
#include "Stage.h"



StageStats Stage::getStats() {
    StageStats stats;
    stats.primCount = static_cast<int>(primMaps.size());
    stats.attributeCount = static_cast<int>(attributeImpls.size());
    return stats;
}

std::map<std::string, GenericAttributeImpl*>*  Stage::createPrimMap(const std::string& path) {
    auto * prim = new std::map<std::string, GenericAttributeImpl*>();
    primMaps[path] = prim;
    return prim;
}

Stage::~Stage() {
    for (auto primMap : primMaps){
        delete primMap.second;
    }
    for(auto attributeImpl : attributeImpls){
        delete attributeImpl;
    }
}
AttributeImpl<int>* getAsIntImpl(GenericAttributeImpl* impl){
    return static_cast<AttributeImpl<int>*>(impl);
}
void Stage::printNice() {
    for(auto primMap : primMaps){
        std::cout << primMap.first << std::endl;
        for(auto primAttr : *(primMap.second)){
            std::cout << "   " << primAttr.second->attr_type << " " << primAttr.first;
            if (primAttr.second->isInt()){
                std::cout << " " << getAsIntImpl(primAttr.second)->value << std::endl;
            }
        }
    }
}


