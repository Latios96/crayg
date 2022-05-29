//
// Created by Jan on 29.05.2022.
//

#include "UsdRenderSettingsTranslator.h"
#include <pxr/base/gf/vec2i.h>
#include "UsdUtils.h"

namespace crayg {

UsdRenderSettingsTranslator::UsdRenderSettingsTranslator(const pxr::UsdRenderSettings &usdPrim) : BaseUsdTranslator(
    usdPrim) {}

std::shared_ptr<crayg::RenderSettings> crayg::UsdRenderSettingsTranslator::translate() {
    auto renderSettings = BaseUsdTranslator::translate();

    Resolution resolution = Resolution(1280, 720);
    if (usdPrim.GetResolutionAttr() && usdPrim.GetResolutionAttr().IsAuthored()) {
        auto usdResolution = UsdUtils::getAttributeValueAs<pxr::GfVec2i>(usdPrim.GetResolutionAttr());
        resolution = Resolution(usdResolution[0], usdResolution[1]);
    }

    int maxSamples = 4;
    auto maxSamplesAttr = usdPrim.GetPrim().GetAttribute(pxr::TfToken("maxSamples"));
    if (maxSamplesAttr) {
        maxSamples = UsdUtils::getAttributeValueAs<int>(maxSamplesAttr);
    }

    renderSettings->resolution = resolution;
    renderSettings->maxSamples = maxSamples;

    return renderSettings;
}

std::string crayg::UsdRenderSettingsTranslator::getTranslatedType() {
    return "render settings";
}

}