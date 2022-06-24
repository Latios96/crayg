#include "UsdRenderSettingsReader.h"
#include <pxr/base/gf/vec2i.h>
#include "sceneIO/usd/UsdUtils.h"
#include <magic_enum.hpp>
#include <algorithm>

namespace crayg {

UsdRenderSettingsReader::UsdRenderSettingsReader(const pxr::UsdRenderSettings &usdPrim) : BaseUsdReader(
    usdPrim) {}

std::shared_ptr<crayg::RenderSettings> crayg::UsdRenderSettingsReader::read() {
    auto renderSettings = BaseUsdReader::read();

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

    IntegratorType integratorType = IntegratorType::RAYTRACING;
    auto integratorTypeAttr = usdPrim.GetPrim().GetAttribute(pxr::TfToken("integratorType"));
    if (integratorTypeAttr) {
        auto integratorTypeToken = UsdUtils::getAttributeValueAs<pxr::TfToken>(integratorTypeAttr).GetString();
        for (auto &c: integratorTypeToken) c = toupper(c);
        auto maybeValue = magic_enum::enum_cast<IntegratorType>(integratorTypeToken);
        if (!maybeValue.has_value()) {
            throw std::runtime_error(fmt::format(R"(Unsupported Integrator type: "{}")", integratorTypeToken));
        }
        integratorType = maybeValue.value();
    }

    renderSettings->resolution = resolution;
    renderSettings->maxSamples = maxSamples;
    renderSettings->integratorType = integratorType;

    return renderSettings;
}

std::string crayg::UsdRenderSettingsReader::getTranslatedType() {
    return "render settings";
}

}