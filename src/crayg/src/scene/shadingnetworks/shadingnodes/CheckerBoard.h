#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_SHADINGNETWORKS_SHADINGNODES_CHECKERBOARD_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_SHADINGNETWORKS_SHADINGNODES_CHECKERBOARD_H_

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

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_SCENE_SHADINGNETWORKS_SHADINGNODES_CHECKERBOARD_H_
