#pragma once

#include "crayg/foundation/math/geometry/Color.h"
#include "crayg/foundation/math/geometry/Ray.h"
#include "crayg/renderer/integrators/SurfaceInteraction.h"
#include "crayg/scene/shadingnetworks/ShadingNode.h"

namespace crayg {

struct Lobe {
    Color weight;
    Ray sampleDirection;
};

struct Lobes {
    Lobe metallic;
    Lobe specular;
    Lobe diffuse;
    Lobe emission;
};

class Material : public ShadingNode {
  public:
    explicit Material();
    explicit Material(const std::string &name);

    virtual void getLobes(const SurfaceInteraction &surfaceInteraction, Lobes &lobes);
};

}
