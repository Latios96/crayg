#pragma once

#include "crayg/foundation/math/geometry/OrthonormalBasis.h"
#include "crayg/foundation/math/geometry/Ray.h"
#include "crayg/foundation/math/geometry/Vector3f.h"

namespace crayg {

class Imageable;

class SurfaceInteraction {
  public:
    SurfaceInteraction(Imageable &imageable, const Vector3f &point, const Vector3f &normal, const Ray &ray);
    Imageable &imageable;
    Vector3f point;
    Vector3f normal;
    Ray ray;

    Ray spawnRayFromSurface(const Vector3f &direction) const;

    Ray spawnReflectionRayFromSurface() const;

    OrthonormalBasis getOrthonormalBasis() const;
};

}
