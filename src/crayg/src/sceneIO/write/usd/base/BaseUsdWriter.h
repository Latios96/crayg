#pragma once

#include "Logger.h"
#include "sceneIO/usd/CraygUsdBase.h"
#include "sceneIO/write/usd/UsdPathFactory.h"
#include <memory>
#include <pxr/usd/usd/stage.h>

namespace crayg {

template <class UsdType, class CraygType> class BaseUsdWriter {
  public:
    BaseUsdWriter(CraygType &craygObject) : craygObject(craygObject) {
    }

    virtual UsdType write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) {
        const pxr::SdfPath targetPath = usdPathFactory.getPathForName(craygObject.getName(), getTranslatedType());
        Logger::info("Writing {} {}", getTranslatedType(), targetPath);

        auto usdObject = UsdType::Define(stage, targetPath);

        return usdObject;
    }

  protected:
    virtual std::string getTranslatedType() = 0;
    CraygType &craygObject;
};

}
