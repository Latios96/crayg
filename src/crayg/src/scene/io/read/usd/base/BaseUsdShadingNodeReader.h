#pragma once
#include "BaseUsdReader.h"
#include "scene/io/read/usd/shadingnetworks/caches/UsdShadingNodeReadCache.h"
#include "scene/io/usd/UsdConversions.h"
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
