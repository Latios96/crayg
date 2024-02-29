#include "UsdConversionNodesReaders.h"

namespace crayg {

UsdVector2fToColorReader::UsdVector2fToColorReader(const pxr::UsdShadeShader &usdPrim)
    : BaseUsdShadingNodeReader(usdPrim) {
}

std::shared_ptr<Vector2fToColor> UsdVector2fToColorReader::read() {
    auto vector2fToColor = BaseUsdShadingNodeReader::read();

    return vector2fToColor;
}

std::string UsdVector2fToColorReader::getTranslatedType() {
    return "FloatConstant";
}

} // crayg