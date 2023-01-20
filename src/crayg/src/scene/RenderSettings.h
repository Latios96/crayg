#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_RENDERSETTINGS_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_RENDERSETTINGS_H_

#include <basics/Resolution.h>
#include <utils/ToStringHelper.h>
#include "spdlog/fmt/ostr.h"
#include "integrators/IntegratorType.h"
#include "integrators/IntegratorSettings.h"
#include "intersectors/IntersectorType.h"

namespace crayg {

class RenderSettings {
 public:
    RenderSettings();
    RenderSettings(const RenderSettings &renderSettings);
    explicit RenderSettings(const Resolution &resolution,
                            int maxSamples,
                            IntegratorType integratorType,
                            IntegratorSettings integratorSettings, IntersectorType intersectorType);

    bool operator==(const RenderSettings &rhs) const;
    bool operator!=(const RenderSettings &rhs) const;

    friend std::ostream &operator<<(std::ostream &os, const RenderSettings &renderSettings) {
        os << ToStringHelper("RenderSettings")
            .addMember("resolution", renderSettings.resolution)
            .addMember("maxSamples", renderSettings.maxSamples)
            .addMember("integratorType", renderSettings.integratorType)
            .addMember("integratorSettings", renderSettings.integratorSettings)
            .addMember("intersectorType", renderSettings.intersectorType)
            .finish();
        return os;
    }

    Resolution resolution;
    int maxSamples;
    IntegratorType integratorType = IntegratorType::RAYTRACING;
    IntegratorSettings integratorSettings;
    IntersectorType intersectorType = IntersectorType::EMBREE;
};

}

#endif //CRAYG_SRC_CRAYG_SRC_SCENE_RENDERSETTINGS_H_
