//
// Created by Jan Honsbrok on 09.10.18.
//

#ifndef CRAYG_STAGE_H
#define CRAYG_STAGE_H

#include <string>
#include <map>
#include <vector>
#include "AttributeImpl.h"

struct StageStats{
    int primCount;
    int attributeCount;
};

class Stage {
public:

    /*AttributeImpl<int>* createIntAttributeImpl();*/

    std::map<std::string, GenericAttributeImpl*>* createPrimMap(const std::string& path);

    StageStats getStats();

    template <typename T>
    AttributeImpl<T>* createAttributeImpl();

    void printNice();

    virtual ~Stage();

private:
    // todo use AttributeImpl here
    std::map<std::string, std::map<std::string, GenericAttributeImpl*>*> primMaps;
    std::vector<GenericAttributeImpl*> attributeImpls;
};

template <typename T>
std::string getTypeName(){
    if (typeid(T) == typeid(int)){
        return "int";
    }
    else{
        return "unknown";
    }
};

template<typename T>
AttributeImpl<T> *Stage::createAttributeImpl() {
    AttributeImpl<T>* intAttrImpl = new AttributeImpl<int>();
    intAttrImpl->attr_type = getTypeName<int>();
    attributeImpls.push_back(intAttrImpl);
    return intAttrImpl;
}

#endif //CRAYG_STAGE_H
