//
// Created by Jan Honsbrok on 25.11.18.
//

#ifndef CRAYG_IMAGEABLE_H
#define CRAYG_IMAGEABLE_H


#include <intersectors/Intersectable.h>
#include <foundation/Color.h>

class Imageable : public Intersectable{
public:
    virtual Vector3f getNormal(Vector3f point)=0;
    // todo add getColor()

    class Intersection{
    public:
        Intersection(float rayParameter, Imageable *imageable);

        float rayParameter;
        Imageable *imageable;
    };
    virtual Intersection intersect(Ray ray)=0;
};


#endif //CRAYG_IMAGEABLE_H
