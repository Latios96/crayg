//
// Created by Jan on 30.10.2020.
//

#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_RENDERSETTINGS_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_RENDERSETTINGS_H_

#include <basics/Resolution.h>
#include <utils/ToStringHelper.h>
#include "spdlog/fmt/ostr.h"

namespace crayg {

class RenderSettings {
 public:
    RenderSettings();
    RenderSettings(const RenderSettings &renderSettings);
    explicit RenderSettings(const Resolution &resolution, int maxSamples);
    Resolution resolution;
    int maxSamples;
    bool operator==(const RenderSettings &rhs) const;
    bool operator!=(const RenderSettings &rhs) const;

    template<typename OStream>
    friend OStream &operator<<(OStream &os, const RenderSettings &renderSettings) {
        os << ToStringHelper("RenderSettings")
            .addMember("resolution", renderSettings.resolution)
            .addMember("maxSamples", renderSettings.maxSamples)
            .finish();
        return os;
    }
};

}

#endif //CRAYG_SRC_CRAYG_SRC_SCENE_RENDERSETTINGS_H_
