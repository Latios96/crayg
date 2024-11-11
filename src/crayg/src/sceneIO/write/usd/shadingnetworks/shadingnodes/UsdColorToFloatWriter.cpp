#include "UsdColorToFloatWriter.h"
#include "sceneIO/usd/UsdUtils.h"
#include "sceneIO/write/usd/shadingnetworks/caches/UsdShadingNodeWriteCache.h"

namespace crayg {
UsdColorToFloatWriter::UsdColorToFloatWriter(ColorToFloat &craygObject,
                                             UsdShadingNodeWriteCache &usdShadingNodeWriteCache)
    : BaseUsdShadingNodeWriter(craygObject, usdShadingNodeWriteCache) {
}

pxr::UsdShadeShader UsdColorToFloatWriter::write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) {
    auto usdColorToFloat = BaseUsdShadingNodeWriter::write(stage, usdPathFactory);

    usdColorToFloat.CreateIdAttr(pxr::VtValue(pxr::TfToken("crayg:ColorToFloat")));
    usdShadingNodeWriteCache.createInputAndWriteCachedGraph(usdColorToFloat, "colorInput", craygObject.colorInput);
    UsdUtils::createAndSetAttribute(usdColorToFloat.GetPrim(), "colorToFloatMode", craygObject.colorToFloatMode);
    usdColorToFloat.CreateOutput(pxr::TfToken("out"), pxr::SdfValueTypeNames->Float);

    return usdColorToFloat;
}

pxr::UsdShadeOutput UsdColorToFloatWriter::getOutput(pxr::UsdShadeShader &usdShadeShader) {
    return usdShadeShader.GetOutput(pxr::TfToken("out"));
}

std::string UsdColorToFloatWriter::getTranslatedType() {
    return "ColorToFloat";
}
} // crayg