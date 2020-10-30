//
// Created by Jan on 30.10.2020.
//

#include "RenderSettings.h"
RenderSettings::RenderSettings(const Resolution &resolution) : resolution(resolution) {}
const Resolution &RenderSettings::getResolution() const {
    return resolution;
}
RenderSettings::RenderSettings() : resolution(Resolution(0, 0)) {

}
RenderSettings::RenderSettings(const RenderSettings &renderSettings) : resolution(renderSettings.resolution) {

}
void RenderSettings::setResolution(const Resolution &resolution) {
    RenderSettings::resolution = resolution;
}
