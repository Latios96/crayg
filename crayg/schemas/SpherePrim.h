//
// Created by Jan Honsbrok on 13.10.18.
//

#ifndef CRAYG_SPHEREPRIM_H
#define CRAYG_SPHEREPRIM_H


#include "prims/Prim.h"
#include "TransformablePrim.h"

class SpherePrim : public TransformablePrim{
public:
    static SpherePrim defineSpherePrim(const std::string &path, Stage &stage){
        // get the prims attribute map
        auto primMap =  stage.createPrimMap(path);

        SpherePrim spherePrim(primMap);
        spherePrim.definePrimAttributes(stage);
        spherePrim.defineImageableAttributes(stage);
        spherePrim.defineTransformableAttributes(stage);
        spherePrim.defineSphereAttributes(stage);

        // author the type Attribute
        spherePrim.getTypeAttribute().setValue("SpherePrim");

        // now finally create the test prim
        return spherePrim;
    }

    static SpherePrim getSpherePrimAt(const std::string &path, Stage &stage){
        return {stage.getPrimMapAt(path)};
    }

    SpherePrim(std::map<std::string, GenericAttributeImpl *> *primMap);

    Attribute<int> getSizeAttribute(){
        return getAsAttribute<int>("size");
    }

protected:
    void defineSphereAttributes(Stage &stage);

};



#endif //CRAYG_SPHEREPRIM_H
