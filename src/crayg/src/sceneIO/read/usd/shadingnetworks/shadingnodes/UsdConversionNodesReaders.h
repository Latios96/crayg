#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_SHADINGNETWORKS_SHADINGNODES_USDCONVERSIONNODESREADERS_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_SHADINGNETWORKS_SHADINGNODES_USDCONVERSIONNODESREADERS_H_

#include "scene/shadingnetworks/shadingnodes/ConversionNodes.h"
#include "sceneIO/read/usd/base/BaseUsdShadingNodeReader.h"

namespace crayg {

class UsdVector2fToColorReader : public BaseUsdShadingNodeReader<Vector2fToColor> {
  public:
    explicit UsdVector2fToColorReader(const pxr::UsdShadeShader &usdPrim,
                                      UsdShadingNodeReadCache &usdShadingNodeReadCache);
    std::shared_ptr<Vector2fToColor> read() override;

  protected:
    std::string getTranslatedType() override;
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_SHADINGNETWORKS_SHADINGNODES_USDCONVERSIONNODESREADERS_H_
