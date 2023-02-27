#include "UsdRenderSettingsWriter.h"
#include <magic_enum.hpp>

namespace crayg {

UsdRenderSettingsWriter::UsdRenderSettingsWriter(const RenderSettings &renderSettings)
    : renderSettings(renderSettings) {
}

pxr::UsdRenderSettings UsdRenderSettingsWriter::write(pxr::UsdStagePtr stage) {
    Logger::info("Writing rendersettings /Render/settings");

    auto usdRenderSettings = pxr::UsdRenderSettings::Define(stage, pxr::SdfPath("/Render/settings"));

    writeResolution(usdRenderSettings);
    writeMaxSamples(usdRenderSettings);
    writeIntegratorType(usdRenderSettings);
    writeIntegratorSettings(usdRenderSettings);
    writeIntersectorType(usdRenderSettings);

    return usdRenderSettings;
}

void UsdRenderSettingsWriter::writeIntegratorType(const pxr::UsdRenderSettings &usdRenderSettings) const {
    usdRenderSettings.GetPrim()
        .CreateAttribute(pxr::TfToken("integratorType"), pxr::SdfValueTypeNames->Token)
        .Set(pxr::TfToken(std::string(magic_enum::enum_name(renderSettings.integratorType))));
}

void UsdRenderSettingsWriter::writeMaxSamples(const pxr::UsdRenderSettings &usdRenderSettings) const {
    usdRenderSettings.GetPrim()
        .CreateAttribute(pxr::TfToken("maxSamples"), pxr::SdfValueTypeNames->Int)
        .Set(renderSettings.maxSamples);
}

void UsdRenderSettingsWriter::writeResolution(const pxr::UsdRenderSettings &usdRenderSettings) const {
    usdRenderSettings.GetResolutionAttr().Set(
        pxr::GfVec2i(renderSettings.resolution.getWidth(), renderSettings.resolution.getHeight()));
}

void UsdRenderSettingsWriter::writeIntegratorSettings(const pxr::UsdRenderSettings &usdRenderSettings) const {
    for (const auto &entry : renderSettings.integratorSettings.settings) {
        switch (entry.second.index()) {
        case 0:
            usdRenderSettings.GetPrim()
                .CreateAttribute(pxr::TfToken(entry.first), pxr::SdfValueTypeNames->Token)
                .Set(pxr::TfToken(std::get<std::string>(entry.second)));
            break;
        case 1:
            usdRenderSettings.GetPrim()
                .CreateAttribute(pxr::TfToken(entry.first), pxr::SdfValueTypeNames->Int)
                .Set(std::get<int>(entry.second));
            break;
        case 2:
            usdRenderSettings.GetPrim()
                .CreateAttribute(pxr::TfToken(entry.first), pxr::SdfValueTypeNames->Float)
                .Set(std::get<float>(entry.second));
            break;
        }
    }
}

void UsdRenderSettingsWriter::writeIntersectorType(const pxr::UsdRenderSettings &usdRenderSettings) const {
    usdRenderSettings.GetPrim()
        .CreateAttribute(pxr::TfToken("intersectorType"), pxr::SdfValueTypeNames->Token)
        .Set(pxr::TfToken(std::string(magic_enum::enum_name(renderSettings.intersectorType))));
}

} // crayg