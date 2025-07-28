#pragma once

#include "BaseUsdReader.h"
#include "sceneIO/usd/UsdReadUtils.h"
#include <memory>

namespace crayg {

template <class UsdType, class CraygType> class BaseUsdXformableReader : public BaseUsdReader<UsdType, CraygType> {
  public:
    BaseUsdXformableReader(const UsdType &usdPrim) : BaseUsdReader<UsdType, CraygType>(usdPrim) {
    }

    std::shared_ptr<CraygType> read() override {
        auto craygObject = BaseUsdReader<UsdType, CraygType>::read();

        UsdReadUtils::readTransform(*craygObject, this->usdPrim, this->timeCodeToRead);

        return craygObject;
    }
};

}
