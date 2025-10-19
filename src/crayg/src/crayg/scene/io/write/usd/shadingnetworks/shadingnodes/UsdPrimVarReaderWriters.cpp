#include "UsdPrimVarReaderWriters.h"
#include "crayg/scene/io/usd/UsdUtils.h"

namespace crayg {
UsdPrimVarReaderVector2fWriter::UsdPrimVarReaderVector2fWriter(PrimVarReaderVector2f &craygObject,
                                                               UsdShadingNodeWriteCache &usdShadingNodeWriteCache)
    : BaseUsdShadingNodeWriter(craygObject, usdShadingNodeWriteCache) {
}

pxr::UsdShadeShader UsdPrimVarReaderVector2fWriter::write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) {
    auto usdShadeShader = BaseUsdShadingNodeWriter::write(stage, usdPathFactory);

    usdShadeShader.CreateIdAttr(pxr::VtValue(pxr::TfToken("crayg:PrimVarReaderVector2f")));
    UsdUtils::createAndSetAttribute(usdShadeShader.GetPrim(), "primVarReaderType", craygObject.primVarReaderType);
    usdShadeShader.CreateOutput(pxr::TfToken("out"), pxr::SdfValueTypeNames->Color3f);

    return usdShadeShader;
}

pxr::UsdShadeOutput UsdPrimVarReaderVector2fWriter::getOutput(pxr::UsdShadeShader &usdShadeShader) {
    return usdShadeShader.GetOutput(pxr::TfToken("out"));
}

std::string UsdPrimVarReaderVector2fWriter::getTranslatedType() {
    return "PrimVarReaderVector2f";
}
}
