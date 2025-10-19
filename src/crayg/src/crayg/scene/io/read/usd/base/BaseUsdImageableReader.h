#pragma once

#include "crayg/scene/io/read/usd/base/BaseUsdXformableReader.h"
#include "crayg/scene/io/read/usd/shadingnetworks/caches/UsdMaterialReadCache.h"
#include "crayg/scene/io/usd/UsdReadUtils.h"
#include <memory>

namespace crayg {

template <class UsdType, class CraygType>
class BaseUsdImageableReader : public BaseUsdXformableReader<UsdType, CraygType> {
  public:
    BaseUsdImageableReader(const UsdType &usdPrim, UsdMaterialReadCache &usdMaterialTranslationCache)
        : BaseUsdXformableReader<UsdType, CraygType>(usdPrim),
          usdMaterialTranslationCache(usdMaterialTranslationCache) {
    }

    std::shared_ptr<CraygType> read() override {
        auto craygObject = BaseUsdXformableReader<UsdType, CraygType>::read();

        const pxr::UsdPrim &prim = this->usdPrim.GetPrim();
        craygObject->setMaterial(usdMaterialTranslationCache.getCachedReadPrimMaterial(prim));
        craygObject->setName(this->usdPrim.GetPrim().GetPath().GetString());

        return craygObject;
    }

  protected:
    UsdMaterialReadCache &usdMaterialTranslationCache;
};

}
