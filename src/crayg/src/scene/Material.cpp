#include "Material.h"
#include "basics/Ray.h"
#include "basics/Vector3f.h"

namespace crayg {

Material::Material(const std::string &name) : ShadingNode(name) {}
Material::Material() : ShadingNode() {}

SurfaceInteraction::SurfaceInteraction(const crayg::Vector3f &point,
                                       const crayg::Vector3f &normal,
                                       const crayg::Ray &ray)
    : point(point), normal(normal), ray(ray) {}
}