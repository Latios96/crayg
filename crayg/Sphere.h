//
// Created by jan on 19.08.18.
//

#ifndef CRAYG_SPHERE_H
#define CRAYG_SPHERE_H


#include "Intersectable.h"
#include "Transformable.h"
#include "string"
#include "sceneIO/Serializable.h"


class Deserializer{
public:
    int readInt();
};

class SceneObject : public Intersectable,
                    public Transformable,
                    public Serializable{
public:
    SceneObject();

    explicit SceneObject(Vector3f position);
    void serialize(Serializer& serializer) override;
};

class Sphere :  public SceneObject{
public:
    Vector3f intersect(Ray ray) override;
    bool intersects(Ray ray) override;

    Sphere(Vector3f position, float radius);

    float getRadius() const;

    void serialize(Serializer& serializer) override;

    virtual ~Sphere();

private:
    float radius;
};



#endif //CRAYG_SPHERE_H
