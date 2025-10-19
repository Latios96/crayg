#pragma once

#include "crayg/scene/io/read/usd/shadingnetworks/caches/UsdShadingNodeReadCache.h"
#include "crayg/scene/io/usd/UsdConversions.h"
#include "crayg/scene/io/usd/UsdUtils.h"
#include <pxr/usd/usdShade/shader.h>
#include <string>

namespace crayg {

class UsdShadingNodeReadUtils {
  public:
    template <typename T, typename UsdType, typename InputType>
    static void readShaderInput(pxr::UsdShadeShader &shader, const std::string &attributeName, InputType &target,
                                UsdShadingNodeReadCache &usdShadingNodeReadCache);
    template <typename T, typename UsdType>
    static void readShaderAttributeValue(const pxr::UsdShadeShader &shader, const std::string &attributeName,
                                         T &target);

    template <typename T, typename UsdType> static T readValue(const pxr::UsdShadeInput &input);
};

template <typename T, typename UsdType> T UsdShadingNodeReadUtils::readValue(const pxr::UsdShadeInput &input) {
    auto value = UsdUtils::getAttributeValueAs<UsdType>(input, pxr::UsdTimeCode::Default());
    return UsdConversions::convert(value);
}

template <typename T, typename UsdType>
void UsdShadingNodeReadUtils::readShaderAttributeValue(const pxr::UsdShadeShader &shader,
                                                       const std::string &attributeName, T &target) {
    auto input = shader.GetInput(pxr::TfToken(attributeName));

    if (!input || !input.GetAttr().HasValue()) {
        return;
    }

    target = readValue<T, UsdType>(input);
}

template <typename T, typename UsdType, typename InputType>
void UsdShadingNodeReadUtils::readShaderInput(pxr::UsdShadeShader &shader, const std::string &attributeName,
                                              InputType &target, UsdShadingNodeReadCache &usdShadingNodeReadCache) {
    auto input = shader.GetInput(pxr::TfToken(attributeName));

    if (!input) {
        return;
    }

    usdShadingNodeReadCache.readCachedGraph(shader, input, target);
}

template <> Color UsdShadingNodeReadUtils::readValue<Color, pxr::GfVec3f>(const pxr::UsdShadeInput &input);
template <> Color UsdShadingNodeReadUtils::readValue<Color, pxr::GfVec4f>(const pxr::UsdShadeInput &input);

template <> bool UsdShadingNodeReadUtils::readValue<bool, int>(const pxr::UsdShadeInput &input);

template <> float UsdShadingNodeReadUtils::readValue<float, float>(const pxr::UsdShadeInput &input);

}
