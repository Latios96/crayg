#pragma once

#include "integrators/IntegratorContext.h"
#include "integrators/SurfaceInteraction.h"
#include "scene/shadingnetworks/ShadingNode.h"
#include <basics/Color.h>
#include <basics/Ray.h>

namespace crayg {

class Material : public ShadingNode {
  public:
    explicit Material();
    explicit Material(const std::string &name);

    virtual Color evaluate(const SurfaceInteraction &surfaceInteraction, IntegratorContext &integratorContext) = 0;
};

} // namespace crayg
