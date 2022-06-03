//
// Created by Jan on 21.05.2022.
//

#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_BASEUSDSCENEOBJECTWRITER_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_BASEUSDSCENEOBJECTWRITER_H_

#include <memory>
#include "Logger.h"
#include "sceneIO/usd/CraygUsdBase.h"
#include "UsdPathFactory.h"
#include "BaseUsdTransformableWriter.h"
#include <pxr/usd/usd/stage.h>
#include "sceneIO/usd/UsdConversions.h"

namespace crayg {

template<class UsdType, class CraygType>
class BaseUsdSceneObjectWriter : public BaseUsdTransformableWriter<UsdType, CraygType> {
 public:
    BaseUsdSceneObjectWriter(const std::shared_ptr<CraygType> &craygObject) : BaseUsdTransformableWriter<UsdType,
                                                                                                         CraygType>(
        craygObject) {}

 protected:
    std::string getTranslatedType() override {
        return this->craygObject->getType();
    }

};

} // crayg

#endif //CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_BASEUSDSCENEOBJECTWRITER_H_
