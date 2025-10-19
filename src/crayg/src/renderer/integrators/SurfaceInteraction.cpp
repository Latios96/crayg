#include "SurfaceInteraction.h"

namespace crayg {

SurfaceInteraction::SurfaceInteraction(Imageable &imageable, const crayg::Vector3f &point,
                                       const crayg::Vector3f &normal, const crayg::Ray &ray)
    : imageable(imageable), point(point), normal(normal), ray(ray) {
}

Ray SurfaceInteraction::spawnRayFromSurface(const Vector3f &direction) const {
    return {point, direction};
}

Ray SurfaceInteraction::spawnReflectionRayFromSurface() const {
    return spawnRayFromSurface(ray.direction.reflect(normal));
}

OrthonormalBasis SurfaceInteraction::getOrthonormalBasis() const {
    return OrthonormalBasis(normal);
}

}