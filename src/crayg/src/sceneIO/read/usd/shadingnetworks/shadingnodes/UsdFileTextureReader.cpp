#include "UsdFileTextureReader.h"

namespace crayg {
UsdFileTextureReader::UsdFileTextureReader(const pxr::UsdShadeShader &usdPrim,
                                           UsdShadingNodeReadCache &usdShadingNodeReadCache)
    : BaseUsdShadingNodeReader(usdPrim, usdShadingNodeReadCache) {
}

std::shared_ptr<FileTexture> UsdFileTextureReader::read() {
    auto fileTexture = BaseUsdShadingNodeReader::read();

    const auto id = UsdUtils::getStaticAttributeValueAs<pxr::TfToken>(usdPrim.GetIdAttr());
    if (id == pxr::TfToken("UsdUVTexture")) {
        readUsdUvTextureUsd(fileTexture);
    } else if (id == pxr::TfToken("crayg:FileTexture")) {
        readCraygFileTexture(fileTexture);
    }

    return fileTexture;
}

std::string UsdFileTextureReader::getTranslatedType() {
    return "FileTexture";
}

void UsdFileTextureReader::readUsdUvTextureUsd(std::shared_ptr<FileTexture> &fileTexture) {
    readFilePath(fileTexture);
    UsdShadingNodeReadUtils::readShaderInput<Vector2f, pxr::GfVec2f>(usdPrim, "st", fileTexture->uvInput,
                                                                     usdShadingNodeReadCache);
    UsdShadingNodeReadUtils::readShaderAttributeValue<Color, pxr::GfVec4f>(usdPrim, "fallback",
                                                                           fileTexture->fallbackColor);
}

void UsdFileTextureReader::readCraygFileTexture(std::shared_ptr<FileTexture> &fileTexture) {
    readFilePath(fileTexture);
    UsdShadingNodeReadUtils::readShaderInput<Vector2f, pxr::GfVec2f>(usdPrim, "uvInput", fileTexture->uvInput,
                                                                     usdShadingNodeReadCache);
    UsdShadingNodeReadUtils::readShaderAttributeValue<Color, pxr::GfVec4f>(usdPrim, "fallbackColor",
                                                                           fileTexture->fallbackColor);
}

void UsdFileTextureReader::readFilePath(std::shared_ptr<FileTexture> &fileTexture) const {
    auto input = usdPrim.GetInput(pxr::TfToken("file"));

    if (!input || !input.GetAttr().HasValue()) {
        Logger::warning("No file input attr found for file texture {}", usdPrim.GetPath());
        return;
    }
    auto fileAttribute = input.GetAttr();
    auto fileAssetPath = UsdUtils::getStaticAttributeValueAs<pxr::SdfAssetPath>(fileAttribute);
    auto filePath =
        fileAssetPath.GetResolvedPath().empty() ? fileAssetPath.GetAssetPath() : fileAssetPath.GetResolvedPath();
    Logger::info("{} file path resolved to {}", usdPrim.GetPath(), filePath);
    fileTexture->setFilePath(filePath);
}
} // crayg