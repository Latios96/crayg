//
// Created by Jan on 21.05.2022.
//

#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_BASEUSDXFORMABLETRANSLATOR_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_BASEUSDXFORMABLETRANSLATOR_H_

#include <memory>
#include "Logger.h"
#include "BaseUsdTranslator.h"
#include "UsdTranslatorUtils.h"

namespace crayg {

template<class UsdType, class CraygType>
class BaseUsdXformableTranslator : public BaseUsdTranslator<UsdType, CraygType> {
 public:
    BaseUsdXformableTranslator(const UsdType &usdPrim) : BaseUsdTranslator<UsdType, CraygType>(usdPrim) {

    }
    std::shared_ptr<CraygType> translate() override {
        auto craygObject = BaseUsdTranslator<UsdType, CraygType>::translate();

        UsdTranslatorUtils::translateTransform(*craygObject, usdPrim);

        return craygObject;
    }
};

} // crayg

#endif //CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_BASEUSDXFORMABLETRANSLATOR_H_
