#include "UsdConstantShadingNodeWriters.h"
#include "sceneIO/usd/UsdConversions.h"

namespace crayg {

UsdFloatConstantWriter::UsdFloatConstantWriter(FloatConstant &craygObject,
                                               UsdShadingNodeWriteCache &usdShadingNodeWriteCache)
    : BaseUsdShadingNodeWriter(craygObject, usdShadingNodeWriteCache) {
}

pxr::UsdShadeShader UsdFloatConstantWriter::write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) {
    auto usdShadeShader = BaseUsdShadingNodeWriter::write(stage, usdPathFactory);

    usdShadeShader.CreateIdAttr(pxr::VtValue(pxr::TfToken("crayg:FloatConstant")));
    usdShadeShader.CreateInput(pxr::TfToken("value"), pxr::SdfValueTypeNames->Float).Set(craygObject.value);
    usdShadeShader.CreateOutput(pxr::TfToken("out"), pxr::SdfValueTypeNames->Float);

    return usdShadeShader;
}

pxr::UsdShadeOutput UsdFloatConstantWriter::getOutput(pxr::UsdShadeShader &usdShadeShader) {
    return usdShadeShader.GetOutput(pxr::TfToken("out"));
}

std::string UsdFloatConstantWriter::getTranslatedType() {
    return "FloatConstant";
}

UsdIntConstantWriter::UsdIntConstantWriter(IntConstant &craygObject, UsdShadingNodeWriteCache &usdShadingNodeWriteCache)
    : BaseUsdShadingNodeWriter(craygObject, usdShadingNodeWriteCache) {
}

pxr::UsdShadeShader UsdIntConstantWriter::write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) {
    auto usdShadeShader = BaseUsdShadingNodeWriter::write(stage, usdPathFactory);

    usdShadeShader.CreateIdAttr(pxr::VtValue(pxr::TfToken("crayg:IntConstant")));
    usdShadeShader.CreateInput(pxr::TfToken("value"), pxr::SdfValueTypeNames->Int).Set(craygObject.value);
    usdShadeShader.CreateOutput(pxr::TfToken("out"), pxr::SdfValueTypeNames->Int);

    return usdShadeShader;
}

pxr::UsdShadeOutput UsdIntConstantWriter::getOutput(pxr::UsdShadeShader &usdShadeShader) {
    return usdShadeShader.GetOutput(pxr::TfToken("out"));
}

std::string UsdIntConstantWriter::getTranslatedType() {
    return "IntConstant";
}

UsdVector2fConstantWriter::UsdVector2fConstantWriter(Vector2fConstant &craygObject,
                                                     UsdShadingNodeWriteCache &usdShadingNodeWriteCache)
    : BaseUsdShadingNodeWriter(craygObject, usdShadingNodeWriteCache) {
}

pxr::UsdShadeShader UsdVector2fConstantWriter::write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) {
    auto usdShadeShader = BaseUsdShadingNodeWriter::write(stage, usdPathFactory);

    usdShadeShader.CreateIdAttr(pxr::VtValue(pxr::TfToken("crayg:Vector2fConstant")));
    usdShadeShader.CreateInput(pxr::TfToken("value"), pxr::SdfValueTypeNames->Float2)
        .Set(UsdConversions::convert(craygObject.value));
    usdShadeShader.CreateOutput(pxr::TfToken("out"), pxr::SdfValueTypeNames->Float2);

    return usdShadeShader;
}

pxr::UsdShadeOutput UsdVector2fConstantWriter::getOutput(pxr::UsdShadeShader &usdShadeShader) {
    return usdShadeShader.GetOutput(pxr::TfToken("out"));
}

std::string UsdVector2fConstantWriter::getTranslatedType() {
    return "Vector2fConstant";
}

UsdColorConstantWriter::UsdColorConstantWriter(ColorConstant &craygObject,
                                               UsdShadingNodeWriteCache &usdShadingNodeWriteCache)
    : BaseUsdShadingNodeWriter(craygObject, usdShadingNodeWriteCache) {
}

pxr::UsdShadeShader UsdColorConstantWriter::write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) {
    auto usdShadeShader = BaseUsdShadingNodeWriter::write(stage, usdPathFactory);

    usdShadeShader.CreateIdAttr(pxr::VtValue(pxr::TfToken("crayg:ColorConstant")));
    usdShadeShader.CreateInput(pxr::TfToken("value"), pxr::SdfValueTypeNames->Color3f)
        .Set(UsdConversions::convert(craygObject.value));
    usdShadeShader.CreateOutput(pxr::TfToken("out"), pxr::SdfValueTypeNames->Color3f);

    return usdShadeShader;
}

pxr::UsdShadeOutput UsdColorConstantWriter::getOutput(pxr::UsdShadeShader &usdShadeShader) {
    return usdShadeShader.GetOutput(pxr::TfToken("out"));
}

std::string UsdColorConstantWriter::getTranslatedType() {
    return "ColorConstant";
}

} // crayg