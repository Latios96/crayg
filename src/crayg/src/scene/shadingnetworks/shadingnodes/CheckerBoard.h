#pragma once

#include "scene/shadingnetworks/ShadingNode.h"

namespace crayg {

class CheckerBoard : public ShadingNode {
  public:
    ColorShadingNodeInput colorA;
    ColorShadingNodeInput colorB;
    int repetitions = 4;
    Vector2fShadingNodeInput uvInput;

    Color evaluateColor(const SurfaceInteraction &surfaceInteraction) override;
    std::string getType() const override;
    ShadingNodeOutputType getOutputType() override;
};

}
