#pragma once

#include "scene/shadingnetworks/ShadingNode.h"

namespace crayg {

class Vector2fToColor : public ShadingNode {
  public:
    Vector2fToColor() = default;
    std::string getType() const override;
    ShadingNodeOutputType getOutputType() override;
    Color evaluateColor(const SurfaceInteraction &surfaceInteraction) override;

    Vector2fShadingNodeInput vector2fInput;
};

}
