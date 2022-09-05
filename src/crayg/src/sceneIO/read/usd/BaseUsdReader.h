#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_BASEUSDREADER_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_BASEUSDREADER_H_

#include <memory>
#include "Logger.h"
#include "sceneIO/usd/UsdReadUtils.h"

namespace crayg {

template<class UsdType, class CraygType>
class BaseUsdReader {
 public:
    BaseUsdReader(const UsdType &usdPrim) : usdPrim(usdPrim) {
    }
    virtual std::shared_ptr<CraygType> read() {
        Logger::debug("Read {} {}", getTranslatedType(), usdPrim.GetPath());

        auto craygObject = std::make_shared<CraygType>();

        return craygObject;
    }
 protected:
    virtual std::string getTranslatedType() = 0;
    UsdType usdPrim;
};

} // crayg

#endif //CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_BASEUSDREADER_H_
