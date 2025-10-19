#include "UsdConversionNodesReaders.h"
#include "scene/io/read/usd/shadingnetworks/UsdShadingNodeReadUtils.h"

namespace crayg {

UsdVector2fToColorReader::UsdVector2fToColorReader(const pxr::UsdShadeShader &usdPrim,
                                                   UsdShadingNodeReadCache &usdShadingNodeReadCache)
    : BaseUsdShadingNodeReader(usdPrim, usdShadingNodeReadCache) {
}

std::shared_ptr<Vector2fToColor> UsdVector2fToColorReader::read() {
    auto vector2fToColor = BaseUsdShadingNodeReader::read();

    UsdShadingNodeReadUtils::readShaderInput<Vector2f, pxr::GfVec2f>(
        usdPrim, "vector2fInput", vector2fToColor->vector2fInput, usdShadingNodeReadCache);

    return vector2fToColor;
}

std::string UsdVector2fToColorReader::getTranslatedType() {
    return "Vector2fToColor";
}

}