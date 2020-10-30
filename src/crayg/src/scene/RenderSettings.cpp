//
// Created by Jan on 30.10.2020.
//

#include "RenderSettings.h"
RenderSettings::RenderSettings(const Resolution &resolution, int maxSamples)
    : resolution(resolution), maxSamples(maxSamples) {}

RenderSettings::RenderSettings() : resolution(Resolution(0, 0)) {
    maxSamples = 4;
}
RenderSettings::RenderSettings(const RenderSettings &renderSettings)
    : resolution(renderSettings.resolution), maxSamples(renderSettings.maxSamples) {

}

