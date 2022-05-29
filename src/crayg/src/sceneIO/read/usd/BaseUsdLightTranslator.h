//
// Created by Jan on 29.05.2022.
//

#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_BASEUSDLIGHTTRANSLATOR_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_BASEUSDLIGHTTRANSLATOR_H_

#include "CraygUsdBase.h"
#include "BaseUsdXformableTranslator.h"
#include "UsdUtils.h"

namespace crayg {

template<class UsdType, class CraygType>
class BaseUsdLightTranslator : public BaseUsdXformableTranslator<UsdType, CraygType> {
 public:
    BaseUsdLightTranslator(const UsdType &usdPrim) : BaseUsdXformableTranslator<UsdType, CraygType>(usdPrim) {

    }
    std::shared_ptr<CraygType> translate() override {
        auto craygObject = BaseUsdXformableTranslator<UsdType, CraygType>::translate();

        const auto intensity = UsdUtils::getAttributeValueAs<float>(this->usdPrim.GetIntensityAttr());
        craygObject->setIntensity(intensity);

        craygObject->setName(this->usdPrim.GetPrim().GetPath().GetString());

        return craygObject;
    }
};

} // crayg

#endif //CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_BASEUSDLIGHTTRANSLATOR_H_
