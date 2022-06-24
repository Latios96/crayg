#ifndef CRAYG_LIGHT_H
#define CRAYG_LIGHT_H

#include "scene/Transformable.h"
#include "scene/Imageable.h"

namespace crayg {

class SceneIntersector;

class Light : public Transformable, public Imageable {
 public:
    Light();
    explicit Light(const Transform &transform, float intensity);
    float getIntensity() const;
    BoundingBox getBounds() const override;

    void setIntensity(float intensity);
    const std::string &getName() const;
    void setName(const std::string &name);

    virtual float calculateShadowFactor(SceneIntersector &sceneIntersector, const Vector3f &point);
    Vector3f getNormal(Vector3f point) override;
    Intersection intersect(Ray ray) override;
    bool isIntersecting(Ray ray) override;
    virtual std::string getType();
 private:
    float intensity = 1;
    std::string name;
 protected:
    constexpr static const float NO_SHADOW = 1.0f;
    constexpr static const float FULL_SHADOW = 0.0f;

};

}
#endif //CRAYG_L