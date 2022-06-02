//
// Created by Jan on 21.05.2022.
//

#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_BASEUSDTRANSFORMABLEWRITER_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_BASEUSDTRANSFORMABLEWRITER_H_

#include <memory>
#include "Logger.h"
#include "sceneIO/usd/CraygUsdBase.h"
#include "UsdPathFactory.h"
#include "BaseUsdWriter.h"
#include <pxr/usd/usd/stage.h>
#include "sceneIO/usd/UsdConversions.h"

namespace crayg {

template<class UsdType, class CraygType>
class BaseUsdTransformableWriter : public BaseUsdWriter<UsdType, CraygType> {
 public:
    BaseUsdTransformableWriter(const std::shared_ptr<CraygType> &craygObject) : BaseUsdWriter<UsdType, CraygType>(
        craygObject) {}

    virtual UsdType write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) {
        auto usdObject = BaseUsdWriter<UsdType, CraygType>::write(stage, usdPathFactory);

        usdObject.MakeMatrixXform().Set(UsdConversions::convert(this->craygObject->getTransform().matrix));

        return usdObject;
    }

};

} // crayg

#endif //CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_BASEUSDTRANSFORMABLEWRITER_H_
