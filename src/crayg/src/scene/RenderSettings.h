#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_RENDERSETTINGS_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_RENDERSETTINGS_H_

#include <basics/Resolution.h>
#include <utils/ToStringHelper.h>
#include "spdlog/fmt/ostr.h"
#include "integrators/IntegratorType.h"

namespace crayg {

class RenderSettings {
 public:
    RenderSettings();
    RenderSettings(const RenderSettings &renderSettings);
    explicit RenderSettings(const Resolution &resolution, int maxSamples, IntegratorType integratorType);

    bool operator==(const RenderSettings &rhs) const;
    bool operator!=(const RenderSettings &rhs) const;

    friend std::ostream &operator<<(std::ostream &os, const RenderSettings &renderSettings) {
        os << ToStringHelper("RenderSettings")
            .addMember("resolution", renderSettings.resolution)
            .addMember("maxSamples", renderSettings.maxSamples)
            .finish();
        return os;
    }

    Resolution resolution;
    int maxSamples;
    IntegratorType integratorType = IntegratorType::RAYTRACING;
};

}

#endif //CRAYG_SRC_CRAYG_SRC_SCENE_RENDERSETTINGS_H_
