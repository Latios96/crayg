#include "BaseUsdMaterialReader.h"

namespace crayg {

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