#include "ConstantShadingNodes.h"

namespace crayg {

std::string FloatConstant::getType() const {
    return "FloatConstant";
}

ShadingNodeOutputType FloatConstant::getOutputType() {
    return ShadingNodeOutputType::FLOAT;
}

float FloatConstant::evaluateFloat(const SurfaceInteraction &surfaceInteraction) {
    return value;
}

FloatConstant::FloatConstant(float value) : value(value) {
}

std::string IntConstant::getType() const {
    return "IntConstant";
}

ShadingNodeOutputType IntConstant::getOutputType() {
    return ShadingNodeOutputType::INT;
}

int IntConstant::evaluateInt(const SurfaceInteraction &surfaceInteraction) {
    return value;
}

IntConstant::IntConstant(int value) : value(value) {
}

std::string Vector2fConstant::getType() const {
    return "Vector2fConstant";
}

ShadingNodeOutputType Vector2fConstant::getOutputType() {
    return ShadingNodeOutputType::VECTOR2F;
}

Vector2f Vector2fConstant::evaluateVector2f(const SurfaceInteraction &surfaceInteraction) {
    return value;
}

Vector2fConstant::Vector2fConstant(const Vector2f &value) : value(value) {
}

std::string ColorConstant::getType() const {
    return "ColorConstant";
}

ShadingNodeOutputType ColorConstant::getOutputType() {
    return ShadingNodeOutputType::COLOR;
}

Color ColorConstant::evaluateColor(const SurfaceInteraction &surfaceInteraction) {
    return value;
}

ColorConstant::ColorConstant(const Color &value) : value(value) {
}
}