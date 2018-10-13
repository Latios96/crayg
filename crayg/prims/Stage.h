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

    AttributeImpl<int>* createIntAttributeImpl();

    std::map<std::string, GenericAttributeImpl*>* createPrimMap(const std::string& path);

    StageStats getStats();

    void printNice();

    virtual ~Stage();

private:
    // todo use AttributeImpl here
    std::map<std::string, std::map<std::string, GenericAttributeImpl*>*> primMaps;
    std::vector<GenericAttributeImpl*> attributeImpls;
};


#endif //CRAYG_STAGE_H
