//
// Created by Jan Honsbrok on 09.10.18.
//

#include "Stage.h"


int Stage::createIntAttributeImpl() {
    attributeImpls.push_back(0);
    return 0;
}

StageStats Stage::getStats() {
    StageStats stats;
    stats.primCount = static_cast<int>(primMaps.size());
    stats.attributeCount = static_cast<int>(attributeImpls.size());
    return stats;
}

std::map<std::string, int>*  Stage::createPrimMap(const std::string& path) {
    auto * prim = new std::map<std::string, int>();
    primMaps[path] = prim;
    return prim;
}
