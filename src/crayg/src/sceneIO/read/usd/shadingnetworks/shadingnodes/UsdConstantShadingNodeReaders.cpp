#include "UsdConstantShadingNodeReaders.h"

namespace crayg {

UsdFloatConstantReader::UsdFloatConstantReader(const pxr::UsdShadeShader &usdPrim,
                                               UsdShadingNodeReadCache &usdShadingNodeReadCache)
    : BaseUsdShadingNodeReader(usdPrim, usdShadingNodeReadCache) {
}

std::shared_ptr<FloatConstant> UsdFloatConstantReader::read() {
    auto floatConstant = BaseUsdShadingNodeReader::read();

    UsdShadingNodeReadUtils::readShaderAttributeValue<float, float>(usdPrim, "value", floatConstant->value);

    return floatConstant;
}

std::string UsdFloatConstantReader::getTranslatedType() {
    return "FloatConstant";
}

UsdIntConstantReader::UsdIntConstantReader(const pxr::UsdShadeShader &usdPrim,
                                           UsdShadingNodeReadCache &usdShadingNodeReadCache)
    : BaseUsdShadingNodeReader(usdPrim, usdShadingNodeReadCache) {
}

std::shared_ptr<IntConstant> UsdIntConstantReader::read() {
    auto intConstant = BaseUsdShadingNodeReader::read();

    UsdShadingNodeReadUtils::readShaderAttributeValue<int, int>(usdPrim, "value", intConstant->value);

    return intConstant;
}

std::string UsdIntConstantReader::getTranslatedType() {
    return "IntConstant";
}

UsdVector2fConstantReader::UsdVector2fConstantReader(const pxr::UsdShadeShader &usdPrim,
                                                     UsdShadingNodeReadCache &usdShadingNodeReadCache)
    : BaseUsdShadingNodeReader(usdPrim, usdShadingNodeReadCache) {
}

std::shared_ptr<Vector2fConstant> UsdVector2fConstantReader::read() {
    auto vector2fConstant = BaseUsdShadingNodeReader::read();

    UsdShadingNodeReadUtils::readShaderAttributeValue<Vector2f, pxr::GfVec2f>(usdPrim, "value",
                                                                              vector2fConstant->value);

    return vector2fConstant;
}

std::string UsdVector2fConstantReader::getTranslatedType() {
    return "Vector2fConstant";
}

UsdColorConstantReader::UsdColorConstantReader(const pxr::UsdShadeShader &usdPrim,
                                               UsdShadingNodeReadCache &usdShadingNodeReadCache)
    : BaseUsdShadingNodeReader(usdPrim, usdShadingNodeReadCache) {
}

std::shared_ptr<ColorConstant> UsdColorConstantReader::read() {
    auto colorConstant = BaseUsdShadingNodeReader::read();

    UsdShadingNodeReadUtils::readShaderAttributeValue<Color, pxr::GfVec3f>(usdPrim, "value", colorConstant->value);

    return colorConstant;
}

std::string UsdColorConstantReader::getTranslatedType() {
    return "ColorConstant";
}

} // crayg