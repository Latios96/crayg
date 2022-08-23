#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_MATERIAL_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_MATERIAL_H_

#include "ShadingNode.h"
#include <basics/Color.h>
#include <basics/Ray.h>

namespace crayg {

class SurfaceInteraction {
public:
  SurfaceInteraction(const Vector3f &point, const Vector3f &normal,
                     const Ray &ray);
  Vector3f point;
  Vector3f normal;
  Ray ray;
};

class Material : public ShadingNode {
public:
  explicit Material();
  explicit Material(const std::string &name);
  virtual Color getDiffuseColor() = 0;
  virtual Color evaluate(const SurfaceInteraction &surfaceInteraction) = 0;
};

} // namespace crayg

#endif // CRAYG_SRC_CRAYG_SRC_SCENE_MATERIAL_H_
