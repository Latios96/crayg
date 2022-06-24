//
// Created by Jan Honsbrok on 25.11.18.
//

#ifndef CRAYG_IMAGEABLE_H
#define CRAYG_IMAGEABLE_H

#include <basics/Color.h>
#include <basics/Ray.h>
#include <memory>
#include <basics/BoundingBox.h>
#include "Material.h"

namespace crayg {

class Imageable : public std::enable_shared_from_this<Imageable> {
 public:
    virtual Vector3f getNormal(Vector3f point) = 0;

    class Intersection {
     public:

        static Intersection createInvalid() {
            return {std::numeric_limits<float>::max(), nullptr};
        }

        Intersection() {
            rayParameter = std::numeric_limits<float>::max();
            imageable = nullptr;
        }

        Intersection(float rayParameter, std::shared_ptr<Imageable> imageable);

        Intersection(const Intersection &intersection) {
            this->rayParameter = intersection.rayParameter;
            this->imageable = intersection.imageable;
        }

        float rayParameter;
        std::shared_ptr<Imageable> imageable;

        bool isValid() const {
            return imageable != nullptr && rayParameter != std::numeric_limits<float>::max();
        }
        static Intersection nearest(const Intersection &first, const Intersection &second);
    };

    virtual Intersection intersect(Ray ray) = 0;

    virtual bool isIntersecting(Ray ray) = 0;

    virtual BoundingBox getBounds() const = 0;

    virtual std::shared_ptr<Material> getMaterial() const;
    void setMaterial(const std::shared_ptr<Material> &material);

 private:
    std::shared_ptr<Material> material;

};

}

#endif //CRAYG_IMAGEABLE_H
