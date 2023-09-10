#include "ConstantShadingNodes.h"

namespace crayg {
std::string FloatConstant::getType() {
    return "FloatConstant";
}

ShadingNodeOutputType FloatConstant::getOutputType() {
    return FLOAT;
}

float FloatConstant::evaluateFloat(const SurfaceInteraction &surfaceInteraction) {
    return value;
}

std::string IntConstant::getType() {
    return "IntConstant";
}

ShadingNodeOutputType IntConstant::getOutputType() {
    return INT;
}

int IntConstant::evaluateInt(const SurfaceInteraction &surfaceInteraction) {
    return value;
}

std::string Vector2fConstant::getType() {
    return "Vector2fConstant";
}

ShadingNodeOutputType Vector2fConstant::getOutputType() {
    return VECTOR2F;
}

Vector2f Vector2fConstant::evaluateVector2f(const SurfaceInteraction &surfaceInteraction) {
    return value;
}

std::string ColorConstant::getType() {
    return "ColorConstant";
}

ShadingNodeOutputType ColorConstant::getOutputType() {
    return COLOR;
}

Color ColorConstant::evaluateColor(const SurfaceInteraction &surfaceInteraction) {
    return {};
}
} // crayg