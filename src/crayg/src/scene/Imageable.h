#ifndef CRAYG_IMAGEABLE_H
#define CRAYG_IMAGEABLE_H

#include "basics/OrthonormalBasis.h"
#include "basics/Transform.h"
#include "shadingnetworks/materials/Material.h"
#include <basics/BoundingBox.h>
#include <basics/Color.h>
#include <basics/Ray.h>
#include <memory>

namespace crayg {

enum class ImageableType { INVALID, TRIANGLE, SPHERE };

class Imageable {
  public:
    virtual Vector3f getNormal(Vector3f point) = 0;
    virtual OrthonormalBasis getOrthonormalBasis(const Vector3f &point);

    class Intersection {
      public:
        static Intersection createInvalid() {
            return {std::numeric_limits<float>::max(), nullptr, ImageableType::INVALID};
        }

        Intersection() {
            rayParameter = std::numeric_limits<float>::max();
            imageable = nullptr;
        }

        Intersection(float rayParameter, Imageable *imageable, ImageableType imageableType);
        Intersection(float rayParameter, Imageable *imageable, bool isOwning, ImageableType imageableType);

        Intersection(const Intersection &intersection) {
            this->rayParameter = intersection.rayParameter;
            this->imageable = intersection.imageable;
            this->imageableType = intersection.imageableType;
        }

        float rayParameter;
        Imageable *imageable;
        bool isOwning = false;
        ImageableType imageableType;

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

  protected:
    Transform *instanceTransform = nullptr;

  private:
    std::shared_ptr<Material> material;
};

}

CRAYG_FMT_ENUM_FORMATTER(crayg::ImageableType);

#endif // CRAYG_IMAGEABLE_H
