#include "UsdFileTextureWriter.h"
#include "scene/io/write/usd/shadingnetworks/caches/UsdShadingNodeWriteCache.h"

namespace crayg {

UsdFileTextureWriter::UsdFileTextureWriter(FileTexture &craygObject, UsdShadingNodeWriteCache &usdShadingNodeWriteCache)
    : BaseUsdShadingNodeWriter(craygObject, usdShadingNodeWriteCache) {
}

pxr::UsdShadeShader UsdFileTextureWriter::write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) {
    auto usdFileTexture = BaseUsdShadingNodeWriter::write(stage, usdPathFactory);

    usdFileTexture.CreateIdAttr(pxr::VtValue(pxr::TfToken("crayg:FileTexture")));
    usdShadingNodeWriteCache.createInputAndWriteCachedGraph(usdFileTexture, "uvInput", craygObject.uvInput);
    usdFileTexture.CreateInput(pxr::TfToken("file"), pxr::SdfValueTypeNames->Asset)
        .Set(pxr::SdfAssetPath(craygObject.getFilePath()));
    usdFileTexture.CreateInput(pxr::TfToken("fallbackColor"), pxr::SdfValueTypeNames->Color4f)
        .Set(pxr::GfVec4f(craygObject.fallbackColor.r, craygObject.fallbackColor.g, craygObject.fallbackColor.b, 1));
    usdFileTexture.CreateOutput(pxr::TfToken("out"), pxr::SdfValueTypeNames->Color3f);

    return usdFileTexture;
}

pxr::UsdShadeOutput UsdFileTextureWriter::getOutput(pxr::UsdShadeShader &usdShadeShader) {
    return usdShadeShader.GetOutput(pxr::TfToken("out"));
}

std::string UsdFileTextureWriter::getTranslatedType() {
    return "FileTexture";
}

}