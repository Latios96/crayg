#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_SHADINGNETWORKS_SHADINGNODES_USDPRIMVARREADERREADERS_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_SHADINGNETWORKS_SHADINGNODES_USDPRIMVARREADERREADERS_H_

#include "scene/shadingnetworks/shadingnodes/PrimVarReaders.h"
#include "sceneIO/read/usd/base/BaseUsdShadingNodeReader.h"

namespace crayg {

class UsdPrimVarReaderVector2fReader : public BaseUsdShadingNodeReader<PrimVarReaderVector2f> {
  public:
    explicit UsdPrimVarReaderVector2fReader(const pxr::UsdShadeShader &usdPrim,
                                            UsdShadingNodeReadCache &usdShadingNodeReadCache);
    std::shared_ptr<PrimVarReaderVector2f> read() override;

  protected:
    void readPrimVarReaderTypeFromUsd(std::shared_ptr<PrimVarReaderVector2f> &primVarReader);
    void readPrimVarReaderTypeFromCrayg(std::shared_ptr<PrimVarReaderVector2f> &primVarReader);
    std::string getTranslatedType() override;
    std::string getVarname(const pxr::UsdShadeInput &varnameInput) const;
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_SHADINGNETWORKS_SHADINGNODES_USDPRIMVARREADERREADERS_H_
