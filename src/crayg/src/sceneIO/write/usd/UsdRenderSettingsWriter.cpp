#include <magic_enum.hpp>
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
    usdRenderSettings.GetPrim().CreateAttribute(pxr::TfToken("integratorType"), pxr::SdfValueTypeNames->Token).Set(
        pxr::TfToken(std::string(magic_enum::enum_name(renderSettings.integratorType))));

    return usdRenderSettings;
}

} // crayg