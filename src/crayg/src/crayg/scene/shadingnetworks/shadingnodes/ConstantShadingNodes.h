#pragma once

#include "crayg/scene/shadingnetworks/ShadingNode.h"

namespace crayg {

class FloatConstant : public ShadingNode {
  public:
    FloatConstant() = default;
    FloatConstant(float value);
    std::string getType() const override;
    ShadingNodeOutputType getOutputType() override;
    float evaluateFloat(const SurfaceInteraction &surfaceInteraction) override;

    float value = 0;
};

class IntConstant : public ShadingNode {
  public:
    IntConstant() = default;
    IntConstant(int value);
    std::string getType() const override;
    ShadingNodeOutputType getOutputType() override;
    int evaluateInt(const SurfaceInteraction &surfaceInteraction) override;

    int value = 0;
};

class Vector2fConstant : public ShadingNode {
  public:
    Vector2fConstant() = default;
    Vector2fConstant(const Vector2f &value);
    std::string getType() const override;
    ShadingNodeOutputType getOutputType() override;
    Vector2f evaluateVector2f(const SurfaceInteraction &surfaceInteraction) override;

    Vector2f value;
};

class ColorConstant : public ShadingNode {
  public:
    ColorConstant() = default;
    ColorConstant(const Color &value);
    std::string getType() const override;
    ShadingNodeOutputType getOutputType() override;
    Color evaluateColor(const SurfaceInteraction &surfaceInteraction) override;
    Color value;
};

}
