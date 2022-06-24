#include "RenderSettings.h"

namespace crayg {

RenderSettings::RenderSettings(const Resolution &resolution, int maxSamples, IntegratorType integratorType)
    : resolution(resolution), maxSamples(maxSamples), integratorType(integratorType) {}

RenderSettings::RenderSettings() : resolution(Resolution(0, 0)) {
    maxSamples = 4;
}
RenderSettings::RenderSettings(const RenderSettings &renderSettings)
    : resolution(renderSettings.resolution),
      maxSamples(renderSettings.maxSamples),
      integratorType(renderSettings.integratorType) {

}
bool RenderSettings::operator==(const RenderSettings &rhs) const {
    return resolution == rhs.resolution &&
        maxSamples == rhs.maxSamples;
}
bool RenderSettings::operator!=(const RenderSettings &rhs) const {
    return !(rhs == *this);
}

}

