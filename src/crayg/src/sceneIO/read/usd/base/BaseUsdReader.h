#pragma once

#include "Logger.h"
#include "crayg/foundation/tracing/CraygTracing.h"
#include "sceneIO/usd/UsdReadUtils.h"
#include <compatibility/usd/fmt/SdfPath_formatter.h>
#include <memory>

namespace crayg {

template <class UsdType, class CraygType> class BaseUsdReader {
  public:
    BaseUsdReader(const UsdType &usdPrim) : usdPrim(usdPrim) {
    }

    virtual std::shared_ptr<CraygType> read() {
        CRAYG_TRACE_SCOPE("UsdSceneReader");
        Logger::debug("Read {} {}", getTranslatedType(), usdPrim.GetPath());

        auto craygObject = std::make_shared<CraygType>();

        return craygObject;
    }

  protected:
    virtual std::string getTranslatedType() = 0;
    UsdType usdPrim;
    pxr::UsdTimeCode timeCodeToRead = pxr::UsdTimeCode::EarliestTime();
};

}
