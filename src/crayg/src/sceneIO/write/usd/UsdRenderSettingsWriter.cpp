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
    writeBucketSamplerType(usdRenderSettings);
    writeAdaptiveMaxError(usdRenderSettings);
    writeSamplesPerAdaptivePass(usdRenderSettings);
    writeUseSpectralLensing(usdRenderSettings);
    writeRegionToRender(usdRenderSettings);

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
        std::visit(
            [&entry, &usdRenderSettings](auto &integratorSettingsValue) {
                UsdUtils::createAndSetAttribute(usdRenderSettings.GetPrim(), entry.first, integratorSettingsValue);
            },
            entry.second);
    }
}

void UsdRenderSettingsWriter::writeIntersectorType(const pxr::UsdRenderSettings &usdRenderSettings) const {
    UsdUtils::createAndSetAttribute(usdRenderSettings.GetPrim(), "intersectorType", renderSettings.intersectorType);
}

void UsdRenderSettingsWriter::writeBucketSequenceType(const pxr::UsdRenderSettings &usdRenderSettings) const {
    UsdUtils::createAndSetAttribute(usdRenderSettings.GetPrim(), "bucketSequenceType",
                                    renderSettings.bucketSequenceType);
}

void UsdRenderSettingsWriter::writeBucketSamplerType(const pxr::UsdRenderSettings &usdRenderSettings) const {
    UsdUtils::createAndSetAttribute(usdRenderSettings.GetPrim(), "bucketSamplerType", renderSettings.bucketSamplerType);
}

void UsdRenderSettingsWriter::writeAdaptiveMaxError(const pxr::UsdRenderSettings &usdRenderSettings) const {
    UsdUtils::createAndSetAttribute(usdRenderSettings.GetPrim(), "adaptiveMaxError", renderSettings.adaptiveMaxError);
}

void UsdRenderSettingsWriter::writeSamplesPerAdaptivePass(const pxr::UsdRenderSettings &usdRenderSettings) const {
    UsdUtils::createAndSetAttribute(usdRenderSettings.GetPrim(), "samplesPerAdaptivePass",
                                    renderSettings.samplesPerAdaptivePass);
}

void UsdRenderSettingsWriter::writeUseSpectralLensing(const pxr::UsdRenderSettings &usdRenderSettings) const {
    UsdUtils::createAndSetAttribute(usdRenderSettings.GetPrim(), "useSpectralLensing",
                                    renderSettings.useSpectralLensing ? 1 : 0);
}

void UsdRenderSettingsWriter::writeRegionToRender(const pxr::UsdRenderSettings &usdRenderSettings) const {
    if (!renderSettings.regionToRender) {
        return;
    }

    NDCRegion ndcRegion = renderSettings.regionToRender->toNDCRegion(renderSettings.resolution);
    usdRenderSettings.CreateDataWindowNDCAttr().Set(
        pxr::GfVec4f(ndcRegion.min.x, ndcRegion.min.y, ndcRegion.max.x, ndcRegion.max.y));
}

}