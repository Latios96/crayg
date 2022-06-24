#include "UsdRenderSettingsWriter.h"

namespace crayg {

UsdRenderSettingsWriter::UsdRenderSettingsWriter(const RenderSettings &renderSettings)
    : renderSettings(renderSettings) {}

pxr::UsdRenderSettings UsdRenderSettingsWriter::write(pxr::UsdStagePtr stage) {
    Logger::info("Writing rendersettings /Render/settings");

    auto usdRenderSettings = pxr::UsdRenderSettings::Define(stage, pxr::SdfPath("/Render/settings"));

    usdRenderSettings.GetResolutionAttr().Set(pxr::GfVec2i(renderSettings.resolution.getWidth(),
                                                           renderSettings.resolution.getHeight()));
    usdRenderSettings.GetPrim().CreateAttribute(pxr::TfToken("maxSamples"), pxr::SdfValueTypeNames->Int).Set(
        renderSettings.maxSamples);

    return usdRenderSettings;
}

} // crayg