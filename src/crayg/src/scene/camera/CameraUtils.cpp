#include "CameraUtils.h"

namespace crayg {
float CameraUtils::computeApertureRadius(float focalLength, float fStop) {
    // see "Optical Imaging and Photography", p. 67
    return (focalLength * 0.1f / fStop) / 2.0f;
}
} // crayg