#ifndef CRAYG_SPHERE_H
#define CRAYG_SPHERE_H

#include "string"
#include "SceneObject.h"

namespace crayg {

class Sphere : public SceneObject {
 public:

    Sphere();

    Sphere(Vector3f position, float radius);

    void setRadius(float radius);
    float getRadius() const;

    Sphere::Intersection intersect(Ray ray) override;
    bool isIntersecting(Ray ray) override;
    BoundingBox getBounds() const override;

    Vector3f getNormal(Vector3f point) override;

    std::string getType() override;

    virtual ~Sphere();

 private:
    float radius;
};

}

#endif //CRAYG_SPHERE_H
