#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_BASE_BASEUSDSHADINGNODEREADER_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_BASE_BASEUSDSHADINGNODEREADER_H_
#include "BaseUsdReader.h"
#include "sceneIO/read/usd/shadingnetworks/caches/UsdShadingNodeReadCache.h"
#include "sceneIO/usd/UsdConversions.h"
#include <pxr/usd/usdShade/shader.h>

namespace crayg {

template <class CraygType> class BaseUsdShadingNodeReader : public BaseUsdReader<pxr::UsdShadeShader, CraygType> {
  public:
    BaseUsdShadingNodeReader(const pxr::UsdShadeShader &usdPrim, UsdShadingNodeReadCache &shadingNodeReadCache)
        : BaseUsdReader<pxr::UsdShadeShader, CraygType>(usdPrim), usdShadingNodeReadCache(shadingNodeReadCache) {
    }

    std::shared_ptr<CraygType> read() override {
        auto craygObject = BaseUsdReader<pxr::UsdShadeShader, CraygType>::read();

        craygObject->setName(this->usdPrim.GetPath().GetString());

        return craygObject;
    }

  protected:
    UsdShadingNodeReadCache &usdShadingNodeReadCache;
};

}
#endif // CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_BASE_BASEUSDSHADINGNODEREADER_H_
