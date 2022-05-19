//
// Created by Jan on 19.05.2022.
//

#ifndef CRAYG_SRC_STANDALONE_SRC_CLIRENDERSETTINGSOVERRIDE_H_
#define CRAYG_SRC_STANDALONE_SRC_CLIRENDERSETTINGSOVERRIDE_H_

#include <optional>
#include "basics/Resolution.h"
#include "scene/RenderSettings.h"
namespace crayg {

struct CliRenderSettingsOverride {
    std::optional<Resolution> resolution;
    std::optional<int> maxSamples;

    RenderSettings resolveOverrides(const RenderSettings &renderSettings) const;

    bool hasAnyOverrides() const;

    std::string reportOverrides() const;
};

}

#endif //CRAYG_SRC_STANDALONE_SRC_CLIRENDERSETTINGSOVERRIDE_H_
