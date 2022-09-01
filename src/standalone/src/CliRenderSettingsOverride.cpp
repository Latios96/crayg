#include <boost/algorithm/string/join.hpp>
#include "CliRenderSettingsOverride.h"
#include "Logger.h"

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

    return resolvedRenderSettings;
}

bool CliRenderSettingsOverride::hasAnyOverrides() const {
    return resolution || maxSamples || integratorType;
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
    return boost::algorithm::join(report, ", ");
}

}