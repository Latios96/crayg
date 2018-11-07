//
// Created by Jan Honsbrok on 07.11.18.
//

#ifndef CRAYG_SCENEOBJECT_H
#define CRAYG_SCENEOBJECT_H

#include "intersectors/Intersectable.h"
#include "Transformable.h"
#include "sceneIO/Serializable.h"

class SceneObject : public Intersectable,
                    public Transformable,
                    public Serializable{
public:
    SceneObject();

    explicit SceneObject(Vector3f position);
    void serialize(Serializer& serializer) override;
    void deserialize(Deserializer& deserializer) override;
    virtual Vector3f getNormal(Vector3f point)=0;
};


#endif //CRAYG_SCENEOBJECT_H
