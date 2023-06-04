#include "CameraUtils.h"

namespace crayg {
float CameraUtils::computeApertureRadius(float focalLength_mm, float fStop) {
    // see "Optical Imaging and Photography", p. 67
    return (focalLength_mm * 0.1f / fStop) / 2.0f;
}
} // crayg