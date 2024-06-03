#pragma once

#include "scene/shadingnetworks/shadingnodes/FileTexture.h"
#include "sceneIO/write/usd/base/BaseUsdShadingNodeWriter.h"

namespace crayg {

class UsdFileTextureWriter : public BaseUsdShadingNodeWriter<FileTexture> {
  public:
    explicit UsdFileTextureWriter(FileTexture &craygObject, UsdShadingNodeWriteCache &usdShadingNodeWriteCache);
    pxr::UsdShadeShader write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) override;
    pxr::UsdShadeOutput getOutput(pxr::UsdShadeShader &usdShadeShader) override;

  protected:
    std::string getTranslatedType() override;
};

} // crayg
