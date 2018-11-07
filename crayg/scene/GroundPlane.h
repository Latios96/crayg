//
// Created by Jan Honsbrok on 07.11.18.
//

#ifndef CRAYG_GROUNDPLANE_H
#define CRAYG_GROUNDPLANE_H


#include "SceneObject.h"

class GroundPlane : public SceneObject{
public:
    Ray intersect(Ray ray) override;

    bool intersects(Ray ray) override;

    void serialize(Serializer& serializer) override;

    void deserialize(Deserializer& deserializer) override;

    Vector3f getNormal(Vector3f point) override;

private:
    Vector3f normal = Vector3f(0,1,0);
};


#endif //CRAYG_GROUNDPLANE_H
