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
AttributeImpl<Vector3f>* getAsVector3fImpl(GenericAttributeImpl* impl){
    return static_cast<AttributeImpl<Vector3f>*>(impl);
}
void Stage::printNice() {
    for(auto primMap : primMaps){
        std::cout << primMap.first << std::endl;
        for(auto primAttr : *(primMap.second)){
            std::cout << "   " << primAttr.second->attr_type << " " << primAttr.first;
            if (primAttr.second->isInt()){
                AttributeImpl<int> *impl = getAsIntImpl(primAttr.second);
                std::cout << " " << impl->value << std::endl;
            }
            else if (primAttr.second->isVector3f()){
                Vector3f value = getAsVector3fImpl(primAttr.second)->value;
                std::cout << " " << "x=" << value.x << "y=" << value.y << "z=" << value.z<< std::endl;
            }
        }
    }
}


