#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_BASE_BASEUSDSHADINGNODEREADER_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_BASE_BASEUSDSHADINGNODEREADER_H_
#include "BaseUsdReader.h"
#include "sceneIO/usd/UsdConversions.h"
#include "sceneIO/usd/UsdUtils.h"
#include <pxr/usd/usdShade/shader.h>

namespace crayg {

template <class CraygType> class BaseUsdShadingNodeReader : public BaseUsdReader<pxr::UsdShadeShader, CraygType> {
  public:
    BaseUsdShadingNodeReader(const pxr::UsdShadeShader &usdPrim)
        : BaseUsdReader<pxr::UsdShadeShader, CraygType>(usdPrim) {
    }

    std::shared_ptr<CraygType> read() override {
        auto craygObject = BaseUsdReader<pxr::UsdShadeShader, CraygType>::read();

        craygObject->setName(this->usdPrim.GetPath().GetString());

        return craygObject;
    }
};

class UsdShadingNodeReadUtils {
  public:
    template <typename T, typename UsdType, typename InputType>
    static void readShaderInput(const pxr::UsdShadeShader &shader, const std::string &attributeName, InputType &target);
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
void UsdShadingNodeReadUtils::readShaderInput(const pxr::UsdShadeShader &shader, const std::string &attributeName,
                                              InputType &target) {
    auto input = shader.GetInput(pxr::TfToken(attributeName));

    if (!input || !input.GetAttr().HasValue()) {
        return;
    }

    target.value = readValue<T, UsdType>(input);
}

template <> Color UsdShadingNodeReadUtils::readValue<Color, pxr::GfVec3f>(const pxr::UsdShadeInput &input);

template <> bool UsdShadingNodeReadUtils::readValue<bool, int>(const pxr::UsdShadeInput &input);

template <> float UsdShadingNodeReadUtils::readValue<float, float>(const pxr::UsdShadeInput &input);

}
#endif // CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_BASE_BASEUSDSHADINGNODEREADER_H_
