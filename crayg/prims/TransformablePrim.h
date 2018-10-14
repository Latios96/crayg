//
// Created by Jan Honsbrok on 13.10.18.
//

#ifndef CRAYG_TRANSFORMABLEPRIM_H
#define CRAYG_TRANSFORMABLEPRIM_H


#include "ImageablePrim.h"
#include "Vector3f.h"

class TransformablePrim : public ImageablePrim{
public:
    static TransformablePrim defineTransformablePrim(const std::string &path, Stage &stage){
        // get the prims attribute map
        auto primMap =  stage.createPrimMap(path);

        TransformablePrim transformablePrim(primMap);
        transformablePrim.definePrimAttributes(stage);
        transformablePrim.defineImageableAttributes(stage);
        transformablePrim.defineTransformableAttributes(stage);

        // author the type Attribute
        transformablePrim.getTypeAttribute().setValue("TransformablePrim");

        return transformablePrim;
    }

    TransformablePrim(std::map<std::string, GenericAttributeImpl *> *primMap);

    Attribute<Vector3f> getPositionAttribute(){
            return getAsAttribute<Vector3f>("position");
    }

protected:
    void defineTransformableAttributes(Stage &stage);
};


#endif //CRAYG_TRANSFORMABLEPRIM_H
