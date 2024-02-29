#ifndef CRAYG_SRC_CRAYG_SRC_INTEGRATORS_SURFACEINTERACTION_H_
#define CRAYG_SRC_CRAYG_SRC_INTEGRATORS_SURFACEINTERACTION_H_

#include "basics/Ray.h"
#include "basics/Vector3f.h"

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
};

}
#endif // CRAYG_SRC_CRAYG_SRC_INTEGRATORS_SURFACEINTERACTION_H_
