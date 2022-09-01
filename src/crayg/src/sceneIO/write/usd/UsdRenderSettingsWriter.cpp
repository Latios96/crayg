#include <magic_enum.hpp>
#include "UsdRenderSettingsWriter.h"

namespace crayg {

UsdRenderSettingsWriter::UsdRenderSettingsWriter(const RenderSettings &renderSettings)
    : renderSettings(renderSettings) {}

pxr::UsdRenderSettings UsdRenderSettingsWriter::write(pxr::UsdStagePtr stage) {
    Logger::info("Writing rendersettings /Render/settings");

    auto usdRenderSettings = pxr::UsdRenderSettings::Define(stage, pxr::SdfPath("/Render/settings"));

    writeResolution(usdRenderSettings);
    writeMaxSamples(usdRenderSettings);
    writeIntegratorType(usdRenderSettings);

    return usdRenderSettings;
}
void UsdRenderSettingsWriter::writeIntegratorType(const pxr::UsdRenderSettings &usdRenderSettings) const {
    usdRenderSettings.GetPrim().CreateAttribute(pxr::TfToken("integratorType"), pxr::SdfValueTypeNames->Token).Set(
        pxr::TfToken(std::string(magic_enum::enum_name(renderSettings.integratorType))));
}
void UsdRenderSettingsWriter::writeMaxSamples(const pxr::UsdRenderSettings &usdRenderSettings) const {
    usdRenderSettings.GetPrim().CreateAttribute(pxr::TfToken("maxSamples"), pxr::SdfValueTypeNames->Int).Set(
        renderSettings.maxSamples);
}
void UsdRenderSettingsWriter::writeResolution(const pxr::UsdRenderSettings &usdRenderSettings) const {
    usdRenderSettings.GetResolutionAttr().Set(pxr::GfVec2i(renderSettings.resolution.getWidth(),
                                                           renderSettings.resolution.getHeight()));
}

} // crayg