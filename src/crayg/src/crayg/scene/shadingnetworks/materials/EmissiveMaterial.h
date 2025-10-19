#pragma once
#include "Material.h"

namespace crayg {

class EmissiveMaterial : public Material {
  public:
    EmissiveMaterial();
    explicit EmissiveMaterial(const Color &emission);
    explicit EmissiveMaterial(const std::string &name);
    EmissiveMaterial(const std::string &name, const Color &emission);
    void getLobes(const SurfaceInteraction &surfaceInteraction, Lobes &lobes) override;
    std::string getType() const override;
    ShadingNodeOutputType getOutputType() override;

    Color emission;
};

}
