#pragma once

#include "BaseUsdXformableReader.h"
#include "crayg/scene/io/usd/UsdConversions.h"
#include "crayg/scene/io/usd/UsdUtils.h"

namespace crayg {

template <class UsdType, class CraygType> class BaseUsdLightReader : public BaseUsdXformableReader<UsdType, CraygType> {
  public:
    BaseUsdLightReader(const UsdType &usdPrim) : BaseUsdXformableReader<UsdType, CraygType>(usdPrim) {
    }

    std::shared_ptr<CraygType> read() override {
        auto craygObject = BaseUsdXformableReader<UsdType, CraygType>::read();

        const auto intensity =
            UsdUtils::getAttributeValueAs<float>(this->usdPrim.GetIntensityAttr(), this->timeCodeToRead);
        craygObject->setIntensity(intensity);

        const auto color =
            UsdUtils::getAttributeValueAs<pxr::GfVec3f>(this->usdPrim.GetColorAttr(), this->timeCodeToRead);
        craygObject->setColor(UsdConversions::convertColor(color));

        craygObject->setName(this->usdPrim.GetPrim().GetPath().GetString());

        return craygObject;
    }
};

}
