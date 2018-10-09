//
// Created by Jan Honsbrok on 09.10.18.
//

#ifndef CRAYG_STAGE_H
#define CRAYG_STAGE_H

#include <string>
#include <map>
#include <vector>

struct StageStats{
    int primCount;
    int attributeCount;
};

class Stage {
public:

    int createIntAttributeImpl();

    std::map<std::string, int>* createPrimMap(const std::string& path);

    StageStats getStats();
private:
    // todo use AttributeImpl here
    std::map<std::string, std::map<std::string, int>*> primMaps;
    std::vector<int> attributeImpls;
};


#endif //CRAYG_STAGE_H
