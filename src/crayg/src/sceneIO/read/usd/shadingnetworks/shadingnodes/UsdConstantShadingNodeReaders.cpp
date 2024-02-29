#include "UsdConstantShadingNodeReaders.h"

namespace crayg {

UsdFloatConstantReader::UsdFloatConstantReader(const pxr::UsdShadeShader &usdPrim) : BaseUsdShadingNodeReader(usdPrim) {
}

std::shared_ptr<FloatConstant> UsdFloatConstantReader::read() {
    auto floatConstant = BaseUsdShadingNodeReader::read();

    UsdShadingNodeReadUtils::readShaderAttributeValue<float, float>(usdPrim, "value", floatConstant->value);

    return floatConstant;
}

std::string UsdFloatConstantReader::getTranslatedType() {
    return "FloatConstant";
}

UsdIntConstantReader::UsdIntConstantReader(const pxr::UsdShadeShader &usdPrim) : BaseUsdShadingNodeReader(usdPrim) {
}

std::shared_ptr<IntConstant> UsdIntConstantReader::read() {
    auto IntConstant = BaseUsdShadingNodeReader::read();

    UsdShadingNodeReadUtils::readShaderAttributeValue<int, int>(usdPrim, "value", IntConstant->value);

    return IntConstant;
}

std::string UsdIntConstantReader::getTranslatedType() {
    return "IntConstant";
}

UsdVector2fConstantReader::UsdVector2fConstantReader(const pxr::UsdShadeShader &usdPrim)
    : BaseUsdShadingNodeReader(usdPrim) {
}

std::shared_ptr<Vector2fConstant> UsdVector2fConstantReader::read() {
    auto Vector2fConstant = BaseUsdShadingNodeReader::read();

    UsdShadingNodeReadUtils::readShaderAttributeValue<Vector2f, pxr::GfVec2f>(usdPrim, "value",
                                                                              Vector2fConstant->value);

    return Vector2fConstant;
}

std::string UsdVector2fConstantReader::getTranslatedType() {
    return "Vector2fConstant";
}

UsdColorConstantReader::UsdColorConstantReader(const pxr::UsdShadeShader &usdPrim) : BaseUsdShadingNodeReader(usdPrim) {
}

std::shared_ptr<ColorConstant> UsdColorConstantReader::read() {
    auto ColorConstant = BaseUsdShadingNodeReader::read();

    UsdShadingNodeReadUtils::readShaderAttributeValue<Color, pxr::GfVec3f>(usdPrim, "value", ColorConstant->value);

    return ColorConstant;
}

std::string UsdColorConstantReader::getTranslatedType() {
    return "ColorConstant";
}

} // crayg