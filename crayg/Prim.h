//
// Created by Jan Honsbrok on 09.10.18.
//

#ifndef CRAYG_PRIM_H
#define CRAYG_PRIM_H


#include <string>
#include <map>
#include "Stage.h"

class Prim {
public:

    static Prim definePrim(const std::string& path, Stage& stage);

    // todo get attributes

protected:
    Prim(std::map<std::string, int> *primMap) : primMap(primMap) {}

private:
    std::map<std::string, int>* primMap;
};


#endif //CRAYG_PRIM_H
