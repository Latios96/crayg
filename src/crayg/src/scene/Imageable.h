#pragma once

#include "basics/BoundingBox.h"
#include "basics/Color.h"
#include "basics/OrthonormalBasis.h"
#include "basics/Ray.h"
#include "basics/Transform.h"
#include "shadingnetworks/materials/Material.h"
#include <memory>

namespace crayg {

enum class ImageableType { INVALID, TRIANGLE, SPHERE, LIGHT };

class Imageable {
  public:
    virtual Vector3f getNormal(Vector3f point) = 0;
    virtual OrthonormalBasis getOrthonormalBasis(const Vector3f &point);

    class Intersection {
      public:
        static Intersection createInvalid() {
            return {std::numeric_limits<float>::max(), nullptr};
        }

        Intersection() {
            rayParameter = std::numeric_limits<float>::max();
            imageable = nullptr;
        }

        Intersection(float rayParameter, Imageable *imageable);

        Intersection(const Intersection &intersection) {
            this->rayParameter = intersection.rayParameter;
            this->imageable = intersection.imageable;
        }

        float rayParameter;
        Imageable *imageable;

        bool isValid() const {
            return imageable != nullptr && rayParameter != std::numeric_limits<float>::max();
        }

        static Intersection nearest(const Intersection &first, const Intersection &second);
        virtual ~Intersection();
    };

    virtual Intersection intersect(Ray ray) = 0;

    virtual bool isIntersecting(Ray ray) = 0;

    virtual BoundingBox getBounds() const = 0;

    virtual std::shared_ptr<Material> &getMaterial();
    void setMaterial(const std::shared_ptr<Material> &material);
    virtual ~Imageable() = default;

    ImageableType imageableType;

  protected:
    Transform *instanceTransform = nullptr;

  private:
    std::shared_ptr<Material> material;
};

}
