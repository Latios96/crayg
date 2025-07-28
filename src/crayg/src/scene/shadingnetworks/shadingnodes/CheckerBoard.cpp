#include "CheckerBoard.h"

namespace crayg {
Color CheckerBoard::evaluateColor(const SurfaceInteraction &surfaceInteraction) {
    const Vector2f &uv = uvInput.evaluate(surfaceInteraction);
    float fmodResult = fmod(floor(repetitions * uv.x) + floor(repetitions * uv.y), 2.0);
    if (fmodResult == 0.0) {
        return colorA.evaluate(surfaceInteraction);
    }
    return colorB.evaluate(surfaceInteraction);
}

std::string CheckerBoard::getType() const {
    return "CheckerBoard";
}

ShadingNodeOutputType CheckerBoard::getOutputType() {
    return ShadingNodeOutputType::COLOR;
}
}