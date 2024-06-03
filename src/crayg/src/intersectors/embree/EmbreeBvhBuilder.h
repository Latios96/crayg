#pragma once

#include "EmbreeBvh.h"
#include "scene/Scene.h"
#include "scene/primitives/Sphere.h"
#include "scene/primitives/trianglemesh/TriangleMesh.h"

namespace crayg {

class EmbreeBvhBuilder {
  public:
    EmbreeBvhBuilder(const Scene &scene);
    std::unique_ptr<EmbreeBvh> build() const;

  private:
    const Scene &scene;
};

} // crayg
