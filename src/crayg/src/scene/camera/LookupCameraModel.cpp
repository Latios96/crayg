#include "LookupCameraModel.h"

namespace crayg {
std::optional<Ray> LookupCameraModel::createPrimaryRay(float x, float y) {
    const float relatixeX = x / resolution.getWidth();
    const float relatixeY = y / resolution.getHeight();
    const auto filmPos = filmPhysicalExtend.lerp(relatixeX, relatixeY);
    const Vector3f positionOnFilm = {filmPos.x, filmPos.y, 0};

    return std::nullopt;
    /*if (!tracedRay) {
        return std::nullopt;
    }
    return camera.getTransform().apply(*tracedRay);*/
}

void LookupCameraModel::init() {
    lensRayLookupTable.read("C:\\workspace\\crayg\\src\\crayg\\lensProfiling\\lensfiles\\canon-zoom-70.raylookup");
}
} // crayg