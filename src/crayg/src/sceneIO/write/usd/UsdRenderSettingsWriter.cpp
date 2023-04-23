#include "UsdRenderSettingsWriter.h"
#include "sceneIO/usd/UsdConversions.h"
#include "sceneIO/usd/UsdUtils.h"
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
    writeBucketSequenceType(usdRenderSettings);

    return usdRenderSettings;
}

void UsdRenderSettingsWriter::writeIntegratorType(const pxr::UsdRenderSettings &usdRenderSettings) const {
    UsdUtils::createAndSetAttribute(usdRenderSettings.GetPrim(), "integratorType", renderSettings.integratorType);
}

void UsdRenderSettingsWriter::writeMaxSamples(const pxr::UsdRenderSettings &usdRenderSettings) const {
    UsdUtils::createAndSetAttribute(usdRenderSettings.GetPrim(), "maxSamples", renderSettings.maxSamples);
}

void UsdRenderSettingsWriter::writeResolution(const pxr::UsdRenderSettings &usdRenderSettings) const {
    usdRenderSettings.GetResolutionAttr().Set(UsdConversions::convert(renderSettings.resolution));
}

void UsdRenderSettingsWriter::writeIntegratorSettings(const pxr::UsdRenderSettings &usdRenderSettings) const {
    for (const auto &entry : renderSettings.integratorSettings.settings) {
        switch (entry.second.index()) {
        case 0:
            UsdUtils::createAndSetAttribute(usdRenderSettings.GetPrim(), entry.first,
                                            std::get<std::string>(entry.second));
            break;
        case 1:
            UsdUtils::createAndSetAttribute(usdRenderSettings.GetPrim(), entry.first, std::get<int>(entry.second));
            break;
        case 2:
            UsdUtils::createAndSetAttribute(usdRenderSettings.GetPrim(), entry.first, std::get<float>(entry.second));
            break;
        }
    }
}

void UsdRenderSettingsWriter::writeIntersectorType(const pxr::UsdRenderSettings &usdRenderSettings) const {
    UsdUtils::createAndSetAttribute(usdRenderSettings.GetPrim(), "intersectorType", renderSettings.intersectorType);
}

void UsdRenderSettingsWriter::writeBucketSequenceType(const pxr::UsdRenderSettings &usdRenderSettings) const {
    UsdUtils::createAndSetAttribute(usdRenderSettings.GetPrim(), "bucketSequenceType",
                                    renderSettings.bucketSequenceType);
}

} // crayg