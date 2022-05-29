//
// Created by Jan on 21.05.2022.
//

#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_BASEUSDTRANSLATOR_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_BASEUSDTRANSLATOR_H_

#include <memory>
#include "Logger.h"
#include "UsdTranslatorUtils.h"

namespace crayg {

template<class UsdType, class CraygType>
class BaseUsdTranslator {
 public:
    BaseUsdTranslator(const UsdType &usdPrim) : usdPrim(usdPrim) {
    }
    virtual std::shared_ptr<CraygType> translate() {
        Logger::info("Translating {} {}", getTranslatedType(), usdPrim.GetPath().GetString());

        auto craygObject = std::make_shared<CraygType>();

        return craygObject;
    }
 protected:
    virtual std::string getTranslatedType() = 0;
    UsdType usdPrim;
};

} // crayg

#endif //CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_BASEUSDTRANSLATOR_H_
