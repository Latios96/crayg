#pragma once

#include "EmbreeBvh.h"
#include "crayg/scene/Scene.h"
#include "crayg/scene/primitives/Sphere.h"
#include "crayg/scene/primitives/trianglemesh/TriangleMesh.h"

namespace crayg {

class EmbreeBvhBuilder {
  public:
    EmbreeBvhBuilder(const Scene &scene);
    std::unique_ptr<EmbreeBvh> build() const;

  private:
    const Scene &scene;
};

}
