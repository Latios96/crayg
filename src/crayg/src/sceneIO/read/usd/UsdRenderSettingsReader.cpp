#include "UsdRenderSettingsReader.h"
#include <pxr/base/gf/vec2i.h>
#include "sceneIO/usd/UsdUtils.h"
#include <magic_enum.hpp>

namespace crayg {

UsdRenderSettingsReader::UsdRenderSettingsReader(const pxr::UsdRenderSettings &usdPrim) : BaseUsdReader(
    usdPrim) {}

std::shared_ptr<crayg::RenderSettings> crayg::UsdRenderSettingsReader::read() {
    auto renderSettings = BaseUsdReader::read();

    Resolution resolution = readResolution();
    int maxSamples = readMaxSamples();
    IntegratorType integratorType = readIntegratorType();

    renderSettings->resolution = resolution;
    renderSettings->maxSamples = maxSamples;
    renderSettings->integratorType = integratorType;

    return renderSettings;
}

Resolution crayg::UsdRenderSettingsReader::readResolution() const {
    Resolution resolution = Resolution(1280, 720);
    if (usdPrim.GetResolutionAttr() && usdPrim.GetResolutionAttr().IsAuthored()) {
        auto usdResolution = UsdUtils::getAttributeValueAs<pxr::GfVec2i>(usdPrim.GetResolutionAttr());
        resolution = Resolution(usdResolution[0], usdResolution[1]);
    }
    return resolution;
}

int crayg::UsdRenderSettingsReader::readMaxSamples() const {
    int maxSamples = 4;
    auto maxSamplesAttr = usdPrim.GetPrim().GetAttribute(pxr::TfToken("maxSamples"));
    if (maxSamplesAttr) {
        maxSamples = UsdUtils::getAttributeValueAs<int>(maxSamplesAttr);
    }
    return maxSamples;
}

IntegratorType crayg::UsdRenderSettingsReader::readIntegratorType() const {
    IntegratorType integratorType = IntegratorType::RAYTRACING;
    auto integratorTypeAttr = usdPrim.GetPrim().GetAttribute(pxr::TfToken("integratorType"));
    if (!integratorTypeAttr) {
        return integratorType;
    }
    auto integratorTypeToken = UsdUtils::getAttributeValueAs<pxr::TfToken>(integratorTypeAttr).GetString();
    for (auto &c: integratorTypeToken) c = toupper(c);
    auto maybeValue = magic_enum::enum_cast<IntegratorType>(integratorTypeToken);
    if (!maybeValue.has_value()) {
        throw std::runtime_error(fmt::format(R"(Unsupported Integrator type: "{}")", integratorTypeToken));
    }
    integratorType = maybeValue.value();

    return integratorType;
}

std::string crayg::UsdRenderSettingsReader::getTranslatedType() {
    return "render settings";
}

}