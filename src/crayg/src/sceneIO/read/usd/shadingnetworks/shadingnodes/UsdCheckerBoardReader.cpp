#include "UsdCheckerBoardReader.h"
#include "sceneIO/read/usd/shadingnetworks/UsdShadingNodeReadUtils.h"

namespace crayg {
UsdCheckerBoardReader::UsdCheckerBoardReader(const pxr::UsdShadeShader &usdPrim,
                                             UsdShadingNodeReadCache &usdShadingNodeReadCache)
    : BaseUsdShadingNodeReader(usdPrim, usdShadingNodeReadCache) {
}

std::shared_ptr<CheckerBoard> UsdCheckerBoardReader::read() {
    auto checkerBoard = BaseUsdShadingNodeReader::read();

    UsdShadingNodeReadUtils::readShaderInput<Color, pxr::GfVec3f>(usdPrim, "colorA", checkerBoard->colorA,
                                                                  usdShadingNodeReadCache);
    UsdShadingNodeReadUtils::readShaderInput<Color, pxr::GfVec3f>(usdPrim, "colorB", checkerBoard->colorB,
                                                                  usdShadingNodeReadCache);
    UsdShadingNodeReadUtils::readShaderInput<Vector2f, pxr::GfVec2f>(usdPrim, "uvInput", checkerBoard->uvInput,
                                                                     usdShadingNodeReadCache);

    UsdShadingNodeReadUtils::readShaderAttributeValue<int, int>(usdPrim, "repetitions", checkerBoard->repetitions);

    return checkerBoard;
}

std::string UsdCheckerBoardReader::getTranslatedType() {
    return "CheckerBoard";
}
}