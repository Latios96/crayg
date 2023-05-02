#include "UsdRenderSettingsReader.h"
#include "sceneIO/usd/UsdUtils.h"
#include <boost/algorithm/string/predicate.hpp>
#include <magic_enum.hpp>
#include <pxr/base/gf/vec2i.h>

namespace crayg {

UsdRenderSettingsReader::UsdRenderSettingsReader(const pxr::UsdRenderSettings &usdPrim) : BaseUsdReader(usdPrim) {
}

std::shared_ptr<crayg::RenderSettings> crayg::UsdRenderSettingsReader::read() {
    auto renderSettings = BaseUsdReader::read();

    Resolution resolution = readResolution();
    int maxSamples = readMaxSamples();
    IntegratorType integratorType = readIntegratorType();
    IntegratorSettings integratorSettings = readIntegratorSettings();
    IntersectorType intersectorType = readIntersectorType();
    BucketSequenceType bucketSequenceType = readBucketSequenceType();
    BucketSamplerType bucketSamplerType = readBucketSamplerType();
    float adaptiveMaxError = readAdaptiveMaxError();
    int samplesPerAdaptivePass = readSamplesPerAdaptivePass(); // todo this can all be const

    renderSettings->resolution = resolution;
    renderSettings->maxSamples = maxSamples;
    renderSettings->integratorType = integratorType;
    renderSettings->integratorSettings = integratorSettings;
    renderSettings->intersectorType = intersectorType;
    renderSettings->bucketSequenceType = bucketSequenceType;
    renderSettings->bucketSamplerType = bucketSamplerType;
    renderSettings->adaptiveMaxError = adaptiveMaxError;
    renderSettings->samplesPerAdaptivePass = samplesPerAdaptivePass;

    return renderSettings;
}

Resolution crayg::UsdRenderSettingsReader::readResolution() const {
    Resolution resolution = Resolution(1280, 720); // todo use default from RenderSettings::createDefault() here
    if (usdPrim.GetResolutionAttr() && usdPrim.GetResolutionAttr().IsAuthored()) {
        auto usdResolution = UsdUtils::getStaticAttributeValueAs<pxr::GfVec2i>(usdPrim.GetResolutionAttr());
        resolution = Resolution(usdResolution[0], usdResolution[1]);
    }
    return resolution;
}

int crayg::UsdRenderSettingsReader::readMaxSamples() const {
    return UsdUtils::getStaticAttributeValueAs<int>(usdPrim.GetPrim(), "maxSamples",
                                                    4); // todo use default from RenderSettings::createDefault() here
}

IntegratorType crayg::UsdRenderSettingsReader::readIntegratorType() const {
    return UsdUtils::getAttributeValueAsEnum(usdPrim.GetPrim(), "integratorType", IntegratorType::RAYTRACING);
}

std::string crayg::UsdRenderSettingsReader::getTranslatedType() {
    return "render settings";
}

IntegratorSettings UsdRenderSettingsReader::readIntegratorSettings() const {
    std::unordered_map<std::string, IntegratorSettingsValue> values;
    for (auto &attribute : usdPrim.GetPrim().GetAttributes()) {
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

    throw std::runtime_error(fmt::format("The attribute {} is of type {}, which is not supported. Only token, int and "
                                         "float are suppored as Integrator settings values",
                                         attribute.GetName(), attribute.GetTypeName()));
}

IntersectorType crayg::UsdRenderSettingsReader::readIntersectorType() const {
    return UsdUtils::getAttributeValueAsEnum(usdPrim.GetPrim(), "intersectorType",
                                             RenderSettings::createDefault().intersectorType);
}

BucketSequenceType UsdRenderSettingsReader::readBucketSequenceType() const {
    return UsdUtils::getAttributeValueAsEnum(usdPrim.GetPrim(), "bucketSequenceType",
                                             RenderSettings::createDefault().bucketSequenceType);
}

BucketSamplerType UsdRenderSettingsReader::readBucketSamplerType() {
    return UsdUtils::getAttributeValueAsEnum(usdPrim.GetPrim(), "bucketSamplerType",
                                             RenderSettings::createDefault().bucketSamplerType);
}

float UsdRenderSettingsReader::readAdaptiveMaxError() {
    return UsdUtils::getStaticAttributeValueAs<float>(usdPrim.GetPrim(), "adaptiveMaxError",
                                                      RenderSettings::createDefault().adaptiveMaxError);
}

int UsdRenderSettingsReader::readSamplesPerAdaptivePass() {
    return UsdUtils::getStaticAttributeValueAs<int>(usdPrim.GetPrim(), "samplesPerAdaptivePass",
                                                    RenderSettings::createDefault().samplesPerAdaptivePass);
}

}