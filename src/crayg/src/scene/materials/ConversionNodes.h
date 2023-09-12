#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_MATERIALS_CONVERSIONNODES_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_MATERIALS_CONVERSIONNODES_H_

#include "ShadingNode.h"

namespace crayg {

class Vector2fToColor : public ShadingNode {
  public:
    Vector2fToColor() = default;
    std::string getType() const override;
    ShadingNodeOutputType getOutputType() override;
    Color evaluateColor(const SurfaceInteraction &surfaceInteraction) override;

    Vector2fShadingNodeInput vector2fInput;
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_SCENE_MATERIALS_CONVERSIONNODES_H_
