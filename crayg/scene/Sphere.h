//
// Created by jan on 19.08.18.
//

#ifndef CRAYG_SPHERE_H
#define CRAYG_SPHERE_H


#include "string"
#include "scene/SceneObject.h"

class Sphere :  public SceneObject{
public:

    Sphere();

    Sphere(Vector3f position, float radius);

    float getRadius() const;

    Sphere::Intersection intersect(Ray ray) override;
    bool isIntersecting(Ray ray) override;

    void serialize(Serializer& serializer) override;

    void deserialize(Deserializer& deserializer) override;

    Vector3f getNormal(Vector3f point) override;

    virtual ~Sphere();

private:
    float radius;
};



#endif //CRAYG_SPHERE_H
