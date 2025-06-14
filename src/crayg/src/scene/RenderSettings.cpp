#include "RenderSettings.h"
#include <fmt/std.h>
#include <regex>
#include <utils/Exceptions.h>
#include <utils/ToStringHelper.h>

namespace crayg {

RenderSettings::RenderSettings(const Resolution &resolution, int maxSamples, IntegratorType integratorType,
                               IntegratorSettings integratorSettings, IntersectorType intersectorType,
                               BucketSequenceType bucketSequenceType, BucketSamplerType bucketSamplerType,
                               float maxError, int samplesPerAdaptivePass, bool useSpectralLensing,
                               const std::optional<RegionToRender> &regionToRender)
    : resolution(resolution), maxSamples(maxSamples), integratorType(integratorType),
      integratorSettings(integratorSettings), intersectorType(intersectorType), bucketSequenceType(bucketSequenceType),
      bucketSamplerType(bucketSamplerType), adaptiveMaxError(maxError), samplesPerAdaptivePass(samplesPerAdaptivePass),
      useSpectralLensing(useSpectralLensing), regionToRender(regionToRender) {
}

RenderSettings::RenderSettings() : resolution(Resolution(0, 0)) {
    maxSamples = 4;
}

RenderSettings::RenderSettings(const RenderSettings &renderSettings)
    : resolution(renderSettings.resolution), maxSamples(renderSettings.maxSamples),
      integratorType(renderSettings.integratorType), integratorSettings(renderSettings.integratorSettings),
      intersectorType(renderSettings.intersectorType), bucketSequenceType(renderSettings.bucketSequenceType),
      bucketSamplerType(renderSettings.bucketSamplerType), adaptiveMaxError(renderSettings.adaptiveMaxError),
      samplesPerAdaptivePass(renderSettings.samplesPerAdaptivePass),
      useSpectralLensing(renderSettings.useSpectralLensing), regionToRender(renderSettings.regionToRender) {
}

bool RenderSettings::operator==(const RenderSettings &rhs) const {
    return resolution == rhs.resolution && maxSamples == rhs.maxSamples && integratorType == rhs.integratorType &&
           integratorSettings == rhs.integratorSettings && intersectorType == rhs.intersectorType &&
           bucketSamplerType == rhs.bucketSamplerType && adaptiveMaxError == rhs.adaptiveMaxError &&
           samplesPerAdaptivePass == rhs.samplesPerAdaptivePass && useSpectralLensing == rhs.useSpectralLensing &&
           regionToRender == rhs.regionToRender;
}

bool RenderSettings::operator!=(const RenderSettings &rhs) const {
    return !(rhs == *this);
}

RenderSettings RenderSettings::createDefault() {
    return RenderSettings(crayg::Resolution(1280, 720), 16, IntegratorType::RAYTRACING, IntegratorSettings(),
                          IntersectorType::EMBREE, BucketSequenceType::MORTON, BucketSamplerType::ADAPTIVE, 0.007f, 8,
                          false, std::nullopt);
}

std::ostream &operator<<(std::ostream &os, const RenderSettings &renderSettings) {
    os << ToStringHelper("RenderSettings")
              .addMember("resolution", renderSettings.resolution)
              .addMember("maxSamples", renderSettings.maxSamples)
              .addMember("integratorType", renderSettings.integratorType)
              .addMember("integratorSettings", renderSettings.integratorSettings)
              .addMember("intersectorType", renderSettings.intersectorType)
              .addMember("bucketSequenceType", renderSettings.bucketSequenceType)
              .addMember("bucketSamplerType", renderSettings.bucketSamplerType)
              .addMember("adaptiveMaxError", renderSettings.adaptiveMaxError)
              .addMember("samplesPerAdaptivePass", renderSettings.samplesPerAdaptivePass)
              .addMember("useSpectralLensing", renderSettings.useSpectralLensing)
              .addMember("regionToRender", renderSettings.regionToRender)
              .finish();
    return os;
}

}
