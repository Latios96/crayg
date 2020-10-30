//
// Created by Jan on 30.10.2020.
//

#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_RENDERSETTINGS_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_RENDERSETTINGS_H_

#include <basics/Resolution.h>
class RenderSettings {
 public:
    RenderSettings();
    RenderSettings(const RenderSettings &renderSettings);
    explicit RenderSettings(const Resolution &resolution);
    const Resolution &getResolution() const;
    void setResolution(const Resolution &resolution);
 private:
    Resolution resolution;
};

#endif //CRAYG_SRC_CRAYG_SRC_SCENE_RENDERSETTINGS_H_
