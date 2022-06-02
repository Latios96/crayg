//
// Created by Jan on 29.05.2022.
//

#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_BASEUSDLIGHTREADER_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_BASEUSDLIGHTREADER_H_

#include "sceneIO/usd/CraygUsdBase.h"
#include "BaseUsdXformableReader.h"
#include "sceneIO/usd/UsdUtils.h"

namespace crayg {

template<class UsdType, class CraygType>
class BaseUsdLightReader : public BaseUsdXformableReader<UsdType, CraygType> {
 public:
    BaseUsdLightReader(const UsdType &usdPrim) : BaseUsdXformableReader<UsdType, CraygType>(usdPrim) {

    }
    std::shared_ptr<CraygType> read() override {
        auto craygObject = BaseUsdXformableReader<UsdType, CraygType>::read();

        const auto intensity = UsdUtils::getAttributeValueAs<float>(this->usdPrim.GetIntensityAttr());
        craygObject->setIntensity(intensity);

        craygObject->setName(this->usdPrim.GetPrim().GetPath().GetString());

        return craygObject;
    }
};

} // crayg

#endif //CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_BASEUSDLIGHTREADER_H_
