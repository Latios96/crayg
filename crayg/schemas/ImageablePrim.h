//
// Created by Jan Honsbrok on 13.10.18.
//

#ifndef CRAYG_IMAGABLEPRIM_H
#define CRAYG_IMAGABLEPRIM_H


#include "prims/Prim.h"

class ImageablePrim : public Prim{
public:
    ImageablePrim(std::map<std::string, GenericAttributeImpl*> *primMap) : Prim(primMap) {}

protected:
    void defineImageableAttributes(Stage &stage);
};

#endif //CRAYG_IMAGABLEPRIM_H
