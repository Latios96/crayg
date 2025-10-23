#include "CliRenderSettingsOverride.h"
#include "crayg/foundation/logging/Logger.h"
#include "crayg/foundation/math/geometry/Resolution_formatter.h"
#include <boost/algorithm/string/join.hpp>
#include <fmt/std.h>

namespace crayg {

RenderSettings crayg::CliRenderSettingsOverride::resolveOverrides(const RenderSettings &renderSettings) const {
    RenderSettings resolvedRenderSettings;

    if (!hasAnyOverrides()) {
        return renderSettings;
    }
    Logger::info("Applying rendersetting overrides: {}", reportOverrides());
    resolvedRenderSettings.resolution = resolution.value_or(renderSettings.resolution);
    resolvedRenderSettings.maxSamples = maxSamples.value_or(renderSettings.maxSamples);
    resolvedRenderSettings.integratorType = integratorType.value_or(renderSettings.integratorType);
    resolvedRenderSettings.integratorSettings = integratorSettings.value_or(renderSettings.integratorSettings);
    resolvedRenderSettings.intersectorType = intersectorType.value_or(renderSettings.intersectorType);
    resolvedRenderSettings.tileSequenceType = tileSequenceType.value_or(renderSettings.tileSequenceType);
    resolvedRenderSettings.tileSamplerType = tileSamplerType.value_or(renderSettings.tileSamplerType);
    resolvedRenderSettings.adaptiveMaxError = adaptiveMaxError.value_or(renderSettings.adaptiveMaxError);
    resolvedRenderSettings.samplesPerAdaptivePass =
        samplesPerAdaptivePass.value_or(renderSettings.samplesPerAdaptivePass);
    resolvedRenderSettings.useSpectralLensing = useSpectralLensing.value_or(renderSettings.useSpectralLensing);
    resolvedRenderSettings.regionToRender =
        regionToRender.has_value() ? *regionToRender : renderSettings.regionToRender;

    for (auto &override : integratorSettingsOverrides) {
        resolvedRenderSettings.integratorSettings.settings[override.settingName] = override.value;
    }
    return resolvedRenderSettings;
}

bool CliRenderSettingsOverride::hasAnyOverrides() const {
    return resolution || maxSamples || integratorType || integratorSettings || intersectorType || tileSequenceType ||
           tileSamplerType || adaptiveMaxError || samplesPerAdaptivePass || useSpectralLensing || regionToRender ||
           (!integratorSettingsOverrides.empty());
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
        report.push_back(fmt::format("integratorType -> {}", *integratorType));
    }
    if (integratorSettings) {
        report.push_back(fmt::format("integratorSettings -> {}", *integratorSettings));
    }
    if (intersectorType) {
        report.push_back(fmt::format("intersectorType -> {}", *intersectorType));
    }
    if (tileSequenceType) {
        report.push_back(fmt::format("tileSequenceType -> {}", *tileSequenceType));
    }
    if (tileSamplerType) {
        report.push_back(fmt::format("tileSamplerType -> {}", *tileSamplerType));
    }
    if (adaptiveMaxError) {
        report.push_back(fmt::format("adaptiveMaxError -> {}", *adaptiveMaxError));
    }
    if (samplesPerAdaptivePass) {
        report.push_back(fmt::format("samplesPerAdaptivePass -> {}", *samplesPerAdaptivePass));
    }
    if (useSpectralLensing) {
        report.push_back(fmt::format("useSpectralLensing -> {}", *useSpectralLensing));
    }
    if (regionToRender) {
        report.push_back(fmt::format("regionToRender -> {}", *regionToRender));
    }

    if (!integratorSettingsOverrides.empty()) {
        for (auto &override : integratorSettingsOverrides) {
            report.push_back(fmt::format(R"({} -> {})", override.settingName, override.value));
        }
    }
    return boost::algorithm::join(report, ", ");
}

}