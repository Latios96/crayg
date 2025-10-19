#pragma once

#include "crayg/scene/Imageable.h"
#include "crayg/scene/Transformable.h"

namespace crayg {

class SceneIntersector;

class Light : public Transformable, public Imageable {
  public:
    Light();
    explicit Light(const Transform &transform, float intensity);

    BoundingBox getBounds() const override;

    void setIntensity(float intensity);
    float getIntensity() const;
    const Color &getColor() const;
    void setColor(const Color &color);
    const std::string &getName() const;
    void setName(const std::string &name);

    struct Radiance {
        Color radiance;
        Ray ray;
        Radiance(const Color &radiance, const Ray &ray);
        bool operator==(const Radiance &rhs) const;
        bool operator!=(const Radiance &rhs) const;
        friend std::ostream &operator<<(std::ostream &os, const Radiance &radiance);
    };

    virtual Radiance radiance(const Vector3f &point, const Vector3f &normal);
    Vector3f getNormal(Vector3f point) override;
    Intersection intersect(Ray ray) override;
    bool isIntersecting(Ray ray) override;
    virtual std::string getType();

  private:
    float intensity = 1;
    Color color = Color::createWhite();
    std::string name;
};

}

template <> struct fmt::formatter<crayg::Light::Radiance> : ostream_formatter {};
