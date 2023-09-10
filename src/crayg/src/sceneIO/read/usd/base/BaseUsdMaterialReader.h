#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_BASE_BASEUSDMATERIALREADER_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_BASE_BASEUSDMATERIALREADER_H_
#include "BaseUsdReader.h"
#include "sceneIO/usd/UsdConversions.h"
#include "sceneIO/usd/UsdUtils.h"
#include <pxr/usd/usdShade/shader.h>

namespace crayg {

template <class CraygType> class BaseUsdMaterialReader : public BaseUsdReader<pxr::UsdShadeShader, CraygType> {
  public:
    BaseUsdMaterialReader(const pxr::UsdShadeShader &usdPrim) : BaseUsdReader<pxr::UsdShadeShader, CraygType>(usdPrim) {
    }

    std::shared_ptr<CraygType> read() override {
        auto craygObject = BaseUsdReader<pxr::UsdShadeShader, CraygType>::read();

        craygObject->setName(this->usdPrim.GetPath().GetString());

        return craygObject;
    }
};

class UsdMaterialReadUtils {
  public:
    template <typename T, typename UsdType>
    static void readShaderAttributeValue(const pxr::UsdShadeShader &shader, const std::string &attributeName,
                                         T &target);

    template <typename T, typename UsdType> static T readValue(const pxr::UsdShadeInput &input);
};

template <typename T, typename UsdType> T UsdMaterialReadUtils::readValue(const pxr::UsdShadeInput &input) {
    auto value = UsdUtils::getAttributeValueAs<UsdType>(input, pxr::UsdTimeCode::Default());
    return UsdConversions::convert(value);
}

template <typename T, typename UsdType>
void UsdMaterialReadUtils::readShaderAttributeValue(const pxr::UsdShadeShader &shader, const std::string &attributeName,
                                                    T &target) {
    auto input = shader.GetInput(pxr::TfToken(attributeName));

    if (!input || !input.GetAttr().HasValue()) {
        return;
    }

    target = readValue<T, UsdType>(input);
}

template <> Color UsdMaterialReadUtils::readValue<Color, pxr::GfVec3f>(const pxr::UsdShadeInput &input) {
    auto value = UsdUtils::getAttributeValueAs<pxr::GfVec3f>(input, pxr::UsdTimeCode::Default());
    return UsdConversions::convertColor(value);
}

template <> bool UsdMaterialReadUtils::readValue<bool, int>(const pxr::UsdShadeInput &input) {
    auto value = UsdUtils::getAttributeValueAs<int>(input, pxr::UsdTimeCode::Default());
    return value != 0;
}

template <> float UsdMaterialReadUtils::readValue<float, float>(const pxr::UsdShadeInput &input) {
    return UsdUtils::getAttributeValueAs<float>(input, pxr::UsdTimeCode::Default());
}

}
#endif // CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_BASE_BASEUSDMATERIALREADER_H_
