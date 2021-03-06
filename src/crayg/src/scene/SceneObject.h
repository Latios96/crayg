//
// Created by Jan Honsbrok on 07.11.18.
//

#ifndef CRAYG_SCENEOBJECT_H
#define CRAYG_SCENEOBJECT_H

#include "Transformable.h"
#include "sceneIO/Serializable.h"
#include "Imageable.h"

namespace crayg {

class SceneObject : public Imageable,
                    public Transformable,
                    public Serializable {
 public:
    SceneObject();

    explicit SceneObject(Vector3f position);
    void serialize(Serializer &serializer) override;
    void deserialize(Deserializer &deserializer) override;
    virtual ~SceneObject() = default;
};

}

#endif //CRAYG_SCENEOBJECT_H
