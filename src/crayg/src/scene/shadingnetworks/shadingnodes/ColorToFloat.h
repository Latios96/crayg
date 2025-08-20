#pragma once

#include "scene/shadingnetworks/ShadingNode.h"
#include "utils/EnumFormatter.h"

namespace crayg {

enum class ColorToFloatMode { R, G, B };

class ColorToFloat : public ShadingNode {
  public:
    float evaluateFloat(const SurfaceInteraction &surfaceInteraction) override;
    std::string getType() const override;
    ShadingNodeOutputType getOutputType() override;

    ColorShadingNodeInput colorInput;
    ColorToFloatMode colorToFloatMode;
};

}

CRAYG_FMT_ENUM_FORMATTER_H(crayg::ColorToFloatMode);