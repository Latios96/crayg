#include "ShadingNode.h"
#include "crayg/foundation/math/geometry/Color_formatter.h"
#include "crayg/foundation/math/geometry/Vector2_formatter.h"
#include "crayg/foundation/objects/ToStringHelper.h"
#include <fmt/format.h>
#include <utility>

namespace crayg {

void ShadingNodeInput::connectTo(const std::shared_ptr<ShadingNode> &newInput) {
    if (!newInput) {
        inputNode = nullptr;
        return;
    }
    if (!isCompatibleTo(newInput->getOutputType())) {
        CRAYG_LOG_AND_THROW_RUNTIME_ERROR("Can not connect ShadingNode '{}' of type {} to Input of type {}",
                                          newInput->getName(), newInput->getOutputType(), getOutputType());
    }
    inputNode = newInput;
}

ShadingNodeInput::~ShadingNodeInput() {
}

bool ShadingNodeInput::operator==(const ShadingNodeInput &rhs) const {
    return inputNode == rhs.inputNode;
}

bool ShadingNodeInput::operator!=(const ShadingNodeInput &rhs) const {
    return !(rhs == *this);
}

bool ShadingNodeInput::hasInputConnection() const {
    return inputNode != nullptr;
}

ShadingNodeOutputType FloatShadingNodeInput::getOutputType() const {
    return ShadingNodeOutputType::FLOAT;
}

bool FloatShadingNodeInput::isCompatibleTo(ShadingNodeOutputType shadingNodeType) const {
    return shadingNodeType == ShadingNodeOutputType::FLOAT || shadingNodeType == ShadingNodeOutputType::INT;
}

float FloatShadingNodeInput::evaluate(const SurfaceInteraction &surfaceInteraction) {
    if (inputNode) {
        return inputNode->evaluateFloat(surfaceInteraction);
    }
    return value;
}

FloatShadingNodeInput::FloatShadingNodeInput(float value) : value(value) {
}

bool FloatShadingNodeInput::operator==(const FloatShadingNodeInput &rhs) const {
    return static_cast<const crayg::ShadingNodeInput &>(*this) == static_cast<const crayg::ShadingNodeInput &>(rhs) &&
           value == rhs.value;
}

bool FloatShadingNodeInput::operator!=(const FloatShadingNodeInput &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const FloatShadingNodeInput &input) {
    os << ToStringHelper("FloatShadingNodeInput")
              .addMember("value", input.value)
              .addMember("inputNode", input.inputNode->getName())
              .finish();
    return os;
}

ShadingNodeOutputType IntShadingNodeInput::getOutputType() const {
    return ShadingNodeOutputType::INT;
}

bool IntShadingNodeInput::isCompatibleTo(ShadingNodeOutputType shadingNodeType) const {
    return shadingNodeType == ShadingNodeOutputType::FLOAT || shadingNodeType == ShadingNodeOutputType::INT;
}

int IntShadingNodeInput::evaluate(const SurfaceInteraction &surfaceInteraction) {
    if (inputNode) {
        return inputNode->evaluateInt(surfaceInteraction);
    }
    return value;
}

IntShadingNodeInput::IntShadingNodeInput(int value) : value(value) {
}

bool IntShadingNodeInput::operator==(const IntShadingNodeInput &rhs) const {
    return static_cast<const crayg::ShadingNodeInput &>(*this) == static_cast<const crayg::ShadingNodeInput &>(rhs) &&
           value == rhs.value;
}

bool IntShadingNodeInput::operator!=(const IntShadingNodeInput &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const IntShadingNodeInput &input) {
    os << ToStringHelper("IntShadingNodeInput")
              .addMember("value", input.value)
              .addMember("inputNode", input.inputNode->getName())
              .finish();
    return os;
}

ShadingNodeOutputType Vector2fShadingNodeInput::getOutputType() const {
    return ShadingNodeOutputType::VECTOR2F;
}

bool Vector2fShadingNodeInput::isCompatibleTo(ShadingNodeOutputType shadingNodeType) const {
    return shadingNodeType == ShadingNodeOutputType::VECTOR2F;
}

Vector2f Vector2fShadingNodeInput::evaluate(const SurfaceInteraction &surfaceInteraction) {
    if (inputNode) {
        return inputNode->evaluateVector2f(surfaceInteraction);
    }
    return value;
}

Vector2fShadingNodeInput::Vector2fShadingNodeInput(const Vector2f &value) : value(value) {
}

bool Vector2fShadingNodeInput::operator==(const Vector2fShadingNodeInput &rhs) const {
    return static_cast<const crayg::ShadingNodeInput &>(*this) == static_cast<const crayg::ShadingNodeInput &>(rhs) &&
           value == rhs.value;
}

bool Vector2fShadingNodeInput::operator!=(const Vector2fShadingNodeInput &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Vector2fShadingNodeInput &input) {
    os << ToStringHelper("Vector2fShadingNodeInput")
              .addMember("value", input.value)
              .addMember("inputNode", input.inputNode->getName())
              .finish();
    return os;
}

ShadingNodeOutputType ColorShadingNodeInput::getOutputType() const {
    return ShadingNodeOutputType::COLOR;
}

bool ColorShadingNodeInput::isCompatibleTo(ShadingNodeOutputType shadingNodeType) const {
    return shadingNodeType == ShadingNodeOutputType::COLOR;
}

Color ColorShadingNodeInput::evaluate(const SurfaceInteraction &surfaceInteraction) {
    if (inputNode) {
        return inputNode->evaluateColor(surfaceInteraction);
    }
    return value;
}

ColorShadingNodeInput::ColorShadingNodeInput(const Color &value) : value(value) {
}

bool ColorShadingNodeInput::operator==(const ColorShadingNodeInput &rhs) const {
    return static_cast<const crayg::ShadingNodeInput &>(*this) == static_cast<const crayg::ShadingNodeInput &>(rhs) &&
           value == rhs.value;
}

bool ColorShadingNodeInput::operator!=(const ColorShadingNodeInput &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const ColorShadingNodeInput &input) {
    os << ToStringHelper("ColorShadingNodeInput")
              .addMember("value", input.value)
              .addMember("inputNode", input.inputNode->getName())
              .finish();
    return os;
}

ShadingNode::ShadingNode() {
}

ShadingNode::ShadingNode(std::string name) : name(std::move(name)) {
}

std::string ShadingNode::getName() const {
    return name;
}

void ShadingNode::setName(const std::string &name) {
    ShadingNode::name = name;
}

ShadingNode::~ShadingNode() {
}

}

CRAYG_FMT_ENUM_FORMATTER_IMPL(crayg::ShadingNodeOutputType);
