#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_SHADINGNETWORKS_SHADINGNODES_USDFILETEXTUREREADER_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_SHADINGNETWORKS_SHADINGNODES_USDFILETEXTUREREADER_H_

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

#endif // CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_SHADINGNETWORKS_SHADINGNODES_USDFILETEXTUREREADER_H_
