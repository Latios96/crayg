#include "UsdFileTextureReader.h"
#include <filesystem>

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
    fileTexture->colorSpace = UsdUtils::getAttributeValueAsEnum(usdPrim.GetPrim(), "inputs:sourceColorSpace",
                                                                getDefaultColorSpaceFromFilePath(fileTexture));
}

void UsdFileTextureReader::readCraygFileTexture(std::shared_ptr<FileTexture> &fileTexture) {
    readFilePath(fileTexture);
    UsdShadingNodeReadUtils::readShaderInput<Vector2f, pxr::GfVec2f>(usdPrim, "uvInput", fileTexture->uvInput,
                                                                     usdShadingNodeReadCache);
    UsdShadingNodeReadUtils::readShaderAttributeValue<Color, pxr::GfVec4f>(usdPrim, "fallbackColor",
                                                                           fileTexture->fallbackColor);

    fileTexture->colorSpace = UsdUtils::getAttributeValueAsEnum(usdPrim.GetPrim(), "inputs:sourceColorSpace",
                                                                getDefaultColorSpaceFromFilePath(fileTexture));
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

FileTexture::ColorSpace
UsdFileTextureReader::getDefaultColorSpaceFromFilePath(std::shared_ptr<FileTexture> &fileTexture) {
    const std::string filePath = fileTexture->getFilePath();
    std::filesystem::path path(filePath);
    std::string extension = path.extension().string();
    if (extension == ".exr") {
        return FileTexture::ColorSpace::RAW;
    }
    return FileTexture::ColorSpace::S_RGB;
}

} // crayg