#include "UsdConversionNodeWriters.h"
#include "sceneIO/write/usd/shadingnetworks/caches/UsdShadingNodeWriteCache.h"

namespace crayg {

UsdVector2fToColorWriter::UsdVector2fToColorWriter(Vector2fToColor &craygObject,
                                                   UsdShadingNodeWriteCache &usdShadingNodeWriteCache)
    : BaseUsdShadingNodeWriter(craygObject, usdShadingNodeWriteCache) {
}

pxr::UsdShadeShader UsdVector2fToColorWriter::write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) {
    auto usdShadeShader = BaseUsdShadingNodeWriter::write(stage, usdPathFactory);

    usdShadeShader.CreateIdAttr(pxr::VtValue(pxr::TfToken("crayg:Vector2fToColor")));
    usdShadingNodeWriteCache.createInputAndWriteCachedGraph(usdShadeShader, "vector2fInput", craygObject.vector2fInput);

    usdShadeShader.CreateOutput(pxr::TfToken("out"), pxr::SdfValueTypeNames->Color3f);

    return usdShadeShader;
}

pxr::UsdShadeOutput UsdVector2fToColorWriter::getOutput(pxr::UsdShadeShader &usdShadeShader) {
    return usdShadeShader.GetOutput(pxr::TfToken("out"));
}

std::string UsdVector2fToColorWriter::getTranslatedType() {
    return "Vector2fToColor";
}

} // crayg