//
// Created by Jan Honsbrok on 09.10.18.
//

#include "Prim.h"

Prim Prim::definePrim(const std::string &path, Stage &stage) {
    auto primMap = stage.createPrimMap(path);
    return {primMap};
}






