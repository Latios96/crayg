#include "ColorToFloat.h"

namespace crayg {

std::string ColorToFloat::getType() const {
    return "ColorToFloat";
}

ShadingNodeOutputType ColorToFloat::getOutputType() {
    return ShadingNodeOutputType::FLOAT;
}

float ColorToFloat::evaluateFloat(const SurfaceInteraction &surfaceInteraction) {
    const Color evaluatedColor = colorInput.evaluate(surfaceInteraction);
    switch (colorToFloatMode) {
    case ColorToFloatMode::R:
        return evaluatedColor.r;
    case ColorToFloatMode::G:
        return evaluatedColor.g;
    case ColorToFloatMode::B:
        return evaluatedColor.b;
    default:
        return 0;
    }
}
}

CRAYG_FMT_ENUM_FORMATTER_IMPL(crayg::ColorToFloatMode);