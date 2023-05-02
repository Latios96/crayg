#include "CliRenderSettingsOverride.h"
#include "Logger.h"
#include <boost/algorithm/string/join.hpp>

namespace crayg {

RenderSettings crayg::CliRenderSettingsOverride::resolveOverrides(const RenderSettings &renderSettings) const {
    RenderSettings resolvedRenderSettings;

    if (!hasAnyOverrides()) {
        return renderSettings;
    }
    crayg::Logger::info("Applying rendersetting overrides: {}", reportOverrides());

    resolvedRenderSettings.resolution = resolution ? resolution.value() : renderSettings.resolution;
    resolvedRenderSettings.maxSamples = maxSamples ? maxSamples.value() : renderSettings.maxSamples;
    resolvedRenderSettings.integratorType = integratorType ? integratorType.value() : renderSettings.integratorType;
    resolvedRenderSettings.integratorSettings = renderSettings.integratorSettings;
    resolvedRenderSettings.intersectorType = intersectorType ? intersectorType.value() : renderSettings.intersectorType;
    resolvedRenderSettings.bucketSequenceType =
        bucketSequenceType ? bucketSequenceType.value() : renderSettings.bucketSequenceType;
    resolvedRenderSettings.bucketSamplerType =
        bucketSamplerType ? bucketSamplerType.value() : renderSettings.bucketSamplerType;
    resolvedRenderSettings.adaptiveMaxError =
        adaptiveMaxError ? adaptiveMaxError.value() : renderSettings.adaptiveMaxError;
    resolvedRenderSettings.samplesPerAdaptivePass =
        samplesPerAdaptivePass ? samplesPerAdaptivePass.value() : renderSettings.samplesPerAdaptivePass;

    return resolvedRenderSettings;
}

bool CliRenderSettingsOverride::hasAnyOverrides() const {
    return resolution || maxSamples || integratorType || intersectorType || bucketSequenceType || bucketSamplerType ||
           adaptiveMaxError || samplesPerAdaptivePass;
}

std::string CliRenderSettingsOverride::reportOverrides() const {
    std::vector<std::string> report;
    if (resolution) {
        report.push_back(fmt::format("resolution -> {}", *resolution));
    }
    if (maxSamples) {
        report.push_back(fmt::format("maxSamples -> {}", *maxSamples));
    }
    if (integratorType) {
        report.push_back(fmt::format(R"(integratorType -> "{}")", *integratorType));
    }
    if (intersectorType) {
        report.push_back(fmt::format(R"(intersectorType -> "{}")", *intersectorType));
    }
    if (bucketSequenceType) {
        report.push_back(fmt::format(R"(bucketSequenceType -> "{}")", *bucketSequenceType));
    }
    if (bucketSamplerType) {
        report.push_back(fmt::format(R"(bucketSamplerType -> "{}")", *bucketSamplerType));
    }
    if (adaptiveMaxError) {
        report.push_back(fmt::format(R"(adaptiveMaxError -> {})", *adaptiveMaxError));
    }
    if (samplesPerAdaptivePass) {
        report.push_back(fmt::format(R"(samplesPerAdaptivePass -> {})", *samplesPerAdaptivePass));
    }
    return boost::algorithm::join(report, ", ");
}

}