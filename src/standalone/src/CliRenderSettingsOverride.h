#ifndef CRAYG_SRC_STANDALONE_SRC_CLIRENDERSETTINGSOVERRIDE_H_
#define CRAYG_SRC_STANDALONE_SRC_CLIRENDERSETTINGSOVERRIDE_H_

#include "basics/Resolution.h"
#include "scene/RenderSettings.h"
#include <optional>

namespace crayg {

struct CliRenderSettingsOverride {
    std::optional<Resolution> resolution;
    std::optional<int> maxSamples;
    std::optional<IntegratorType> integratorType;
    std::optional<IntersectorType> intersectorType;

    RenderSettings resolveOverrides(const RenderSettings &renderSettings) const;

    bool hasAnyOverrides() const;

    std::string reportOverrides() const;
};

}

#endif // CRAYG_SRC_STANDALONE_SRC_CLIRENDERSETTINGSOVERRIDE_H_
