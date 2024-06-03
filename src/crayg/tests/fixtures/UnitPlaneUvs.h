#pragma once

#include "integrators/SurfaceInteraction.h"
#include "scene/shadingnetworks/ShadingNode.h"

namespace crayg {

class UnitPlaneUvs : public ShadingNode {
  public:
    Vector2f evaluateVector2f(const SurfaceInteraction &surfaceInteraction) override {
        return surfaceInteraction.point.xy();
    }

    std::string getType() const override {
        return "UnitPlaneUvs";
    }

    ShadingNodeOutputType getOutputType() override {
        return ShadingNodeOutputType::VECTOR2F;
    }
};

}
