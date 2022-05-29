//
// Created by Jan on 21.05.2022.
//

#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_BASEUSDIMAGEABLETRANSLATOR_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_BASEUSDIMAGEABLETRANSLATOR_H_

#include <memory>
#include "BaseUsdXformableTranslator.h"
#include "UsdTranslatorUtils.h"
#include "UsdMaterialTranslationCache.h"

namespace crayg {

template<class UsdType, class CraygType>
class BaseUsdImageableTranslator : public BaseUsdXformableTranslator<UsdType, CraygType> {
 public:
    BaseUsdImageableTranslator(const UsdType &usdPrim, UsdMaterialTranslationCache &usdMaterialTranslationCache)
        : BaseUsdXformableTranslator<UsdType, CraygType>(usdPrim),
          usdMaterialTranslationCache(usdMaterialTranslationCache) {}

    std::shared_ptr<CraygType> translate() override {
        auto craygObject = BaseUsdXformableTranslator<UsdType, CraygType>::translate();

        const pxr::UsdPrim &prim = this->usdPrim.GetPrim();
        craygObject->setMaterial(usdMaterialTranslationCache.getTranslatedPrimMaterial(prim));
        craygObject->setName(this->usdPrim.GetPrim().GetPath().GetString());

        return craygObject;
    }
 protected:
    UsdMaterialTranslationCache &usdMaterialTranslationCache;
};

} // crayg

#endif //CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_BASEUSDIMAGEABLETRANSLATOR_H_
