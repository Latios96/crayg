#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_MATERIAL_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_MATERIAL_H_

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

#endif // CRAYG_SRC_CRAYG_SRC_SCENE_MATERIAL_H_
