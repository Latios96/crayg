#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_BASEUSDTRANSFORMABLEWRITER_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_BASEUSDTRANSFORMABLEWRITER_H_

#include "BaseUsdWriter.h"
#include "Logger.h"
#include "sceneIO/usd/CraygUsdBase.h"
#include "sceneIO/usd/UsdConversions.h"
#include "sceneIO/write/usd/UsdPathFactory.h"
#include <memory>
#include <pxr/usd/usd/stage.h>

namespace crayg {

template <class UsdType, class CraygType> class BaseUsdTransformableWriter : public BaseUsdWriter<UsdType, CraygType> {
  public:
    BaseUsdTransformableWriter(CraygType &craygObject) : BaseUsdWriter<UsdType, CraygType>(craygObject) {
    }

    virtual UsdType write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) {
        auto usdObject = BaseUsdWriter<UsdType, CraygType>::write(stage, usdPathFactory);

        usdObject.MakeMatrixXform().Set(UsdConversions::convert(this->craygObject.getTransform().matrix));

        return usdObject;
    }
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_BASEUSDTRANSFORMABLEWRITER_H_
