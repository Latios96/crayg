#pragma once

#include "integrators/SurfaceInteraction.h"
#include "scene/shadingnetworks/ShadingNode.h"
#include <basics/Color.h>
#include <basics/Ray.h>

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
