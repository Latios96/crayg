#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_BASEUSDIMAGEABLEREADER_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_BASEUSDIMAGEABLEREADER_H_

#include "sceneIO/read/usd/base/BaseUsdXformableReader.h"
#include "sceneIO/read/usd/shadingnetworks/caches/UsdMaterialReadCache.h"
#include "sceneIO/usd/UsdReadUtils.h"
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

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_BASEUSDIMAGEABLEREADER_H_
