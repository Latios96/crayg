#pragma once

#include "scene/io/read/usd/base/BaseUsdShadingNodeReader.h"
#include "scene/shadingnetworks/shadingnodes/PrimVarReaders.h"

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
    std::optional<std::string> getVarname();
    std::optional<std::string> getVarnameFromCurrentNode();
    std::optional<std::string> getVarnameFromConnectedNode();
    std::string readVarname(const pxr::UsdShadeInput &varnameInput) const;
};

}
