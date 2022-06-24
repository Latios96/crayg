#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_BASEUSDWRITER_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_BASEUSDWRITER_H_

#include <memory>
#include "Logger.h"
#include "sceneIO/usd/CraygUsdBase.h"
#include "UsdPathFactory.h"
#include <pxr/usd/usd/stage.h>

namespace crayg {

template<class UsdType, class CraygType>
class BaseUsdWriter {
 public:
    BaseUsdWriter(const std::shared_ptr<CraygType> &craygObject) : craygObject(craygObject) {}

    virtual UsdType write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) {
        const pxr::SdfPath targetPath = usdPathFactory.getPathForName(craygObject->getName(), getTranslatedType());
        Logger::info("Writing {} {}", getTranslatedType(), targetPath);

        auto usdObject = UsdType::Define(stage, targetPath);

        return usdObject;
    }
 protected:
    virtual std::string getTranslatedType() = 0;
    std::shared_ptr<CraygType> craygObject;
};

} // crayg

#endif //CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_BASEUSDWRITER_H_
