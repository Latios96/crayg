#include "UsdConstantShadingNodeWriters.h"

namespace crayg {
UsdFloatConstantWriter::UsdFloatConstantWriter(FloatConstant &craygObject) : BaseUsdShadingNodeWriter(craygObject) {
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
} // crayg