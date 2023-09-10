#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_MATERIALS_CONSTANTSHADINGNODES_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_MATERIALS_CONSTANTSHADINGNODES_H_
#include "ShadingNode.h"

namespace crayg {

class FloatConstant : public ShadingNode {
  public:
    std::string getType() override;
    ShadingNodeOutputType getOutputType() override;
    float evaluateFloat(const SurfaceInteraction &surfaceInteraction) override;

    float value;
};

class IntConstant : public ShadingNode {
  public:
    std::string getType() override;
    ShadingNodeOutputType getOutputType() override;
    int evaluateInt(const SurfaceInteraction &surfaceInteraction) override;

    int value;
};

class Vector2fConstant : public ShadingNode {
  public:
    std::string getType() override;
    ShadingNodeOutputType getOutputType() override;
    Vector2f evaluateVector2f(const SurfaceInteraction &surfaceInteraction) override;

    Vector2f value;
};

class ColorConstant : public ShadingNode {
  public:
    std::string getType() override;
    ShadingNodeOutputType getOutputType() override;
    Color evaluateColor(const SurfaceInteraction &surfaceInteraction) override;
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_SCENE_MATERIALS_CONSTANTSHADINGNODES_H_
