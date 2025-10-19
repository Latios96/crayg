#include "UsdColorToFloatReader.h"
#include "scene/io/read/usd/shadingnetworks/UsdShadingNodeReadUtils.h"

namespace crayg {
UsdColorToFloatReader::UsdColorToFloatReader(const pxr::UsdShadeShader &usdPrim,
                                             UsdShadingNodeReadCache &usdShadingNodeReadCache)
    : BaseUsdShadingNodeReader(usdPrim, usdShadingNodeReadCache) {
}

std::shared_ptr<ColorToFloat> UsdColorToFloatReader::read() {
    auto colorToFloat = BaseUsdShadingNodeReader::read();

    UsdShadingNodeReadUtils::readShaderInput<Color, pxr::GfVec3f>(usdPrim, "colorInput", colorToFloat->colorInput,
                                                                  usdShadingNodeReadCache);
    colorToFloat->colorToFloatMode =
        UsdUtils::getAttributeValueAsEnum(usdPrim.GetPrim(), "colorToFloatMode", ColorToFloatMode::R);

    return colorToFloat;
}

std::string UsdColorToFloatReader::getTranslatedType() {
    return "ColorToFloat";
}
}