#include "SurfaceInteraction.h"

namespace crayg {

SurfaceInteraction::SurfaceInteraction(const crayg::Vector3f &point,
                                       const crayg::Vector3f &normal,
                                       const crayg::Ray &ray)
    : point(point), normal(normal), ray(ray) {}

}