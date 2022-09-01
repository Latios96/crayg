#include "RenderSettings.h"

namespace crayg {

RenderSettings::RenderSettings(const Resolution &resolution,
                               int maxSamples,
                               IntegratorType integratorType,
                               IntegratorSettings integratorSettings)
    : resolution(resolution), maxSamples(maxSamples), integratorType(integratorType),
      integratorSettings(integratorSettings) {}

RenderSettings::RenderSettings() : resolution(Resolution(0, 0)) {
    maxSamples = 4;
}
RenderSettings::RenderSettings(const RenderSettings &renderSettings)
    : resolution(renderSettings.resolution),
      maxSamples(renderSettings.maxSamples),
      integratorType(renderSettings.integratorType),
      integratorSettings(renderSettings.integratorSettings) {

}
bool RenderSettings::operator==(const RenderSettings &rhs) const {
    return resolution == rhs.resolution &&
        maxSamples == rhs.maxSamples && integratorType == rhs.integratorType
        && integratorSettings == rhs.integratorSettings;
}
bool RenderSettings::operator!=(const RenderSettings &rhs) const {
    return !(rhs == *this);
}

}

