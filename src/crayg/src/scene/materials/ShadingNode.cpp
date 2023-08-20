#include "ShadingNode.h"
#include <fmt/format.h>
#include <utility>

namespace crayg {

void ShadingNodeInput::connectTo(const std::shared_ptr<ShadingNode> &newInput) {
    if (!isCompatibleTo(newInput->getOutputType())) {
        throw std::runtime_error(fmt::format("Can not connect ShadingNode '{}' of type {} to Input of type {}",
                                             newInput->getName(), newInput->getOutputType(), getOutputType()));
    }
    inputNode = newInput;
}

ShadingNodeInput::~ShadingNodeInput() {
}

ShadingNodeOutputType FloatShadingNodeInput::getOutputType() const {
    return FLOAT;
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

ShadingNodeOutputType IntShadingNodeInput::getOutputType() const {
    return INT;
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

ShadingNodeOutputType Vector2fShadingNodeInput::getOutputType() const {
    return VECTOR2F;
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

ShadingNodeOutputType ColorShadingNodeInput::getOutputType() const {
    return COLOR;
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

ShadingNode::ShadingNode() {
}

ShadingNode::ShadingNode(std::string name) : name(std::move(name)) {
}

std::string ShadingNode::getName() const {
    return name;
}

ShadingNode::~ShadingNode() {
}

}
