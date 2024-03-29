#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_BASEUSDXFORMABLEREADER_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_BASEUSDXFORMABLEREADER_H_

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

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_BASEUSDXFORMABLEREADER_H_
