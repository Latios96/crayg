#include "RenderSettings.h"

namespace crayg {

RenderSettings::RenderSettings(const Resolution &resolution, int maxSamples, IntegratorType integratorType,
                               IntegratorSettings integratorSettings, IntersectorType intersectorType,
                               BucketSequenceType bucketSequenceType)
    : resolution(resolution), maxSamples(maxSamples), integratorType(integratorType),
      integratorSettings(integratorSettings), intersectorType(intersectorType), bucketSequenceType(bucketSequenceType) {
}

RenderSettings::RenderSettings() : resolution(Resolution(0, 0)) {
    maxSamples = 4;
}

RenderSettings::RenderSettings(const RenderSettings &renderSettings)
    : resolution(renderSettings.resolution), maxSamples(renderSettings.maxSamples),
      integratorType(renderSettings.integratorType), integratorSettings(renderSettings.integratorSettings),
      intersectorType(renderSettings.intersectorType), bucketSequenceType(renderSettings.bucketSequenceType) {
}

bool RenderSettings::operator==(const RenderSettings &rhs) const {
    return resolution == rhs.resolution && maxSamples == rhs.maxSamples && integratorType == rhs.integratorType &&
           integratorSettings == rhs.integratorSettings && intersectorType == rhs.intersectorType;
}

bool RenderSettings::operator!=(const RenderSettings &rhs) const {
    return !(rhs == *this);
}

RenderSettings RenderSettings::createDefault() {
    return RenderSettings(crayg::Resolution(1280, 720), 4, IntegratorType::RAYTRACING, IntegratorSettings(),
                          IntersectorType::EMBREE, BucketSequenceType::LINE_BY_LINE);
}

}
