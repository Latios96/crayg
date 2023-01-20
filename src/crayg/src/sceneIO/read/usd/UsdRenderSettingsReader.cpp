#include "UsdRenderSettingsReader.h"
#include <pxr/base/gf/vec2i.h>
#include "sceneIO/usd/UsdUtils.h"
#include <magic_enum.hpp>
#include <boost/algorithm/string/predicate.hpp>

namespace crayg {

template<typename T>
T readEnumValue(pxr::UsdRenderSettings usdPrim, const std::string &attributeName, T defaultValue) {
    auto usdAttr = usdPrim.GetPrim().GetAttribute(pxr::TfToken(attributeName));
    if (!usdAttr) {
        return defaultValue;
    }
    auto tokenValue = UsdUtils::getStaticAttributeValueAs<pxr::TfToken>(usdAttr).GetString();
    for (auto &c: tokenValue) c = toupper(c);
    auto maybeValue = magic_enum::enum_cast<T>(tokenValue);
    if (!maybeValue.has_value()) {
        throw std::runtime_error(fmt::format(R"(Unsupported value for '{}': "{}")", attributeName, tokenValue));
    }
    return maybeValue.value();
}

UsdRenderSettingsReader::UsdRenderSettingsReader(const pxr::UsdRenderSettings &usdPrim) : BaseUsdReader(
    usdPrim) {}

std::shared_ptr<crayg::RenderSettings> crayg::UsdRenderSettingsReader::read() {
    auto renderSettings = BaseUsdReader::read();

    Resolution resolution = readResolution();
    int maxSamples = readMaxSamples();
    IntegratorType integratorType = readIntegratorType();
    IntegratorSettings integratorSettings = readIntegratorSettings();
    IntersectorType intersectorType = readIntersectorType();

    renderSettings->resolution = resolution;
    renderSettings->maxSamples = maxSamples;
    renderSettings->integratorType = integratorType;
    renderSettings->integratorSettings = integratorSettings;
    renderSettings->intersectorType = intersectorType;

    return renderSettings;
}

Resolution crayg::UsdRenderSettingsReader::readResolution() const {
    Resolution resolution = Resolution(1280, 720);
    if (usdPrim.GetResolutionAttr() && usdPrim.GetResolutionAttr().IsAuthored()) {
        auto usdResolution = UsdUtils::getStaticAttributeValueAs<pxr::GfVec2i>(usdPrim.GetResolutionAttr());
        resolution = Resolution(usdResolution[0], usdResolution[1]);
    }
    return resolution;
}

int crayg::UsdRenderSettingsReader::readMaxSamples() const {
    int maxSamples = 4;
    auto maxSamplesAttr = usdPrim.GetPrim().GetAttribute(pxr::TfToken("maxSamples"));
    if (maxSamplesAttr) {
        maxSamples = UsdUtils::getStaticAttributeValueAs<int>(maxSamplesAttr);
    }
    return maxSamples;
}

IntegratorType crayg::UsdRenderSettingsReader::readIntegratorType() const {
    return readEnumValue<IntegratorType>(usdPrim, "integratorType", IntegratorType::RAYTRACING);
}

std::string crayg::UsdRenderSettingsReader::getTranslatedType() {
    return "render settings";
}
IntegratorSettings UsdRenderSettingsReader::readIntegratorSettings() const {
    std::unordered_map<std::string, IntegratorSettingsValue> values;
    for (auto &attribute: usdPrim.GetPrim().GetAttributes()) {
        if (isIntegratorSettingsAttribute(attribute)) {
            values[attribute.GetName().GetString()] = readIntegratorSettingsValue(attribute);
        }
    }
    return IntegratorSettings(values);
}
bool UsdRenderSettingsReader::isIntegratorSettingsAttribute(const pxr::UsdAttribute &attribute) const {
    constexpr auto integratorNames = magic_enum::enum_entries<IntegratorType>();
    const auto attributeName = attribute.GetName().GetString();
    return std::any_of(integratorNames.begin(), integratorNames.end(), [&attributeName](auto &integratorName) {
        return boost::algorithm::istarts_with(attributeName, integratorName.second);
    });
}

IntegratorSettingsValue UsdRenderSettingsReader::readIntegratorSettingsValue(const pxr::UsdAttribute &attribute) const {
    const bool isIntAttribute = attribute.GetTypeName() == pxr::SdfValueTypeNames->Int;
    const bool isFloatAttribute = attribute.GetTypeName() == pxr::SdfValueTypeNames->Float;
    const bool isTokenAttribute = attribute.GetTypeName() == pxr::SdfValueTypeNames->Token;

    if (isIntAttribute) {
        return {UsdUtils::getStaticAttributeValueAs<int>(attribute)};
    } else if (isFloatAttribute) {
        return {UsdUtils::getStaticAttributeValueAs<float>(attribute)};
    } else if (isTokenAttribute) {
        return {UsdUtils::getStaticAttributeValueAs<pxr::TfToken>(attribute).GetString()};
    }

    throw std::runtime_error(fmt::format(
        "The attribute {} is of type {}, which is not supported. Only token, int and float are suppored as Integrator settings values",
        attribute.GetName(),
        attribute.GetTypeName()));
}

IntersectorType crayg::UsdRenderSettingsReader::readIntersectorType() const {
    return readEnumValue<IntersectorType>(usdPrim, "intersectorType", RenderSettings::createDefault().intersectorType);
}

}