//
// Created by Jan Honsbrok on 25.11.18.
//

#ifndef CRAYG_IMAGEABLE_H
#define CRAYG_IMAGEABLE_H

#include <intersectors/Intersectable.h>
#include <foundation/Color.h>

class Imageable : public Intersectable {
 public:
    virtual Vector3f getNormal(Vector3f point) = 0;
    // todo add getColor()

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

        bool isValid() {
            return imageable != nullptr && rayParameter != std::numeric_limits<float>::max();
        }
    };
    virtual Intersection intersect(Ray ray) = 0;

    virtual void beforeRender() {

    };
};

#endif //CRAYG_IMAGEABLE_H
