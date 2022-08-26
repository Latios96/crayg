#ifndef CRAYG_SRC_CRAYG_SRC_INTEGRATORS_SURFACEINTERACTION_H_
#define CRAYG_SRC_CRAYG_SRC_INTEGRATORS_SURFACEINTERACTION_H_

#include "basics/Vector3f.h"
#include "basics/Ray.h"
namespace crayg {
class SurfaceInteraction {
 public:
    SurfaceInteraction(const Vector3f &point, const Vector3f &normal,
                       const Ray &ray);
    Vector3f point;
    Vector3f normal;
    Ray ray;

    Ray spawnRayFromSurface(const Vector3f &direction) const;

    Ray spawnReflectionRayFromSurface() const;
};

}
#endif //CRAYG_SRC_CRAYG_SRC_INTEGRATORS_SURFACEINTERACTION_H_
