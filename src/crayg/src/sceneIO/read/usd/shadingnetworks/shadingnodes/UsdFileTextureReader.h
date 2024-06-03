#pragma once
#include "scene/shadingnetworks/shadingnodes/FileTexture.h"
#include "sceneIO/read/usd/base/BaseUsdShadingNodeReader.h"

namespace crayg {

class UsdFileTextureReader : public BaseUsdShadingNodeReader<FileTexture> {
  public:
    UsdFileTextureReader(const pxr::UsdShadeShader &usdPrim, UsdShadingNodeReadCache &usdShadingNodeReadCache);
    std::shared_ptr<FileTexture> read() override;

  protected:
    void readUsdUvTextureUsd(std::shared_ptr<FileTexture> &fileTexture);
    void readCraygFileTexture(std::shared_ptr<FileTexture> &fileTexture);
    std::string getTranslatedType() override;
    void readFilePath(std::shared_ptr<FileTexture> &fileTexture) const;
    FileTexture::ColorSpace getDefaultColorSpaceFromFilePath(std::shared_ptr<FileTexture> &fileTexture);
};

} // crayg
