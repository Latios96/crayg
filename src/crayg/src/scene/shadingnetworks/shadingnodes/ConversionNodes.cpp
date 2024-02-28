#include "ConversionNodes.h"

namespace crayg {

Color Vector2fToColor::evaluateColor(const SurfaceInteraction &surfaceInteraction) {
    const auto value = vector2fInput.evaluate(surfaceInteraction);
    return Color(value.x, value.y, 0);
}

std::string Vector2fToColor::getType() const {
    return "Vector2fToColor";
}

ShadingNodeOutputType Vector2fToColor::getOutputType() {
    return COLOR;
}

} // crayg