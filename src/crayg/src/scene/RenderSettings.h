//
// Created by Jan on 30.10.2020.
//

#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_RENDERSETTINGS_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_RENDERSETTINGS_H_

#include <basics/Resolution.h>

namespace crayg {

class RenderSettings {
 public:
    RenderSettings();
    RenderSettings(const RenderSettings &renderSettings);
    explicit RenderSettings(const Resolution &resolution, int maxSamples);
    Resolution resolution;
    int maxSamples;
};

}

#endif //CRAYG_SRC_CRAYG_SRC_SCENE_RENDERSETTINGS_H_
