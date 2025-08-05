#pragma once

#include "Logger.h"
#include "sceneIO/write/usd/UsdPathFactory.h"
#include "sceneIO/write/usd/base/BaseUsdWriter.h"
#include "utils/DtoUtils.h"
#include <memory>
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdShade/shader.h>

namespace crayg {

struct UsdShaderAndOutput {
    pxr::UsdShadeShader shader;
    pxr::UsdShadeOutput output;
};

class UsdShadingNodeWriteCache;

template <class CraygType> class BaseUsdShadingNodeWriter : public BaseUsdWriter<pxr::UsdShadeShader, CraygType> {
  public:
    BaseUsdShadingNodeWriter(CraygType &craygObject, UsdShadingNodeWriteCache &usdShadingNodeWriteCache)
        : BaseUsdWriter<pxr::UsdShadeShader, CraygType>(craygObject),
          usdShadingNodeWriteCache(usdShadingNodeWriteCache) {
    }

    virtual pxr::UsdShadeShader write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) {
        const pxr::SdfPath targetPath = usdPathFactory.getPathForName(this->craygObject.getName(), getTranslatedType());
        Logger::info("Writing {} {}", getTranslatedType(), targetPath);

        auto usdShadeShader = pxr::UsdShadeShader::Define(stage, targetPath);

        return usdShadeShader;
    }

    UsdShaderAndOutput writeAndGetShaderAndOutput(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) {
        auto usdShadeShader = write(stage, usdPathFactory);
        return {usdShadeShader, getOutput(usdShadeShader)};
    }

    virtual pxr::UsdShadeOutput getOutput(pxr::UsdShadeShader &usdShadeShader) = 0;

  protected:
    virtual std::string getTranslatedType() = 0;
    UsdShadingNodeWriteCache &usdShadingNodeWriteCache;
};

}
