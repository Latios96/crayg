#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_BASEUSDMATERIALWRITER_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_BASEUSDMATERIALWRITER_H_

#include "Logger.h"
#include "sceneIO/usd/CraygUsdBase.h"
#include "sceneIO/write/usd/UsdPathFactory.h"
#include "sceneIO/write/usd/base/BaseUsdWriter.h"
#include "sceneIO/write/usd/shadingnetworks/caches/UsdShadingNodeWriteCache.h"
#include <memory>
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdShade/material.h>

namespace crayg {

template <class CraygType> class BaseUsdMaterialWriter : public BaseUsdWriter<pxr::UsdShadeMaterial, CraygType> {
  public:
    BaseUsdMaterialWriter(CraygType &craygObject, UsdShadingNodeWriteCache &usdShadingNodeWriteCache)
        : BaseUsdWriter<pxr::UsdShadeMaterial, CraygType>(craygObject),
          usdShadingNodeWriteCache(usdShadingNodeWriteCache) {
    }

    virtual pxr::UsdShadeMaterial write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) {
        const pxr::SdfPath targetPath = usdPathFactory.getPathForName(this->craygObject.getName(), getTranslatedType());
        Logger::info("Writing {} {}", getTranslatedType(), targetPath);

        auto usdShadeMaterial = pxr::UsdShadeMaterial::Define(stage, targetPath);

        auto usdShadeShader = pxr::UsdShadeShader::Define(
            stage, usdShadeMaterial.GetPath().AppendChild(pxr::TfToken(getTranslatedType())));
        usdShadeMaterial.CreateSurfaceOutput().ConnectToSource(usdShadeShader.ConnectableAPI(),
                                                               pxr::TfToken("surface"));
        auto d = usdShadeShader.GetPath().GetString();
        return usdShadeMaterial;
    }

  protected:
    virtual std::string getTranslatedType() = 0;
    UsdShadingNodeWriteCache &usdShadingNodeWriteCache;
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_BASEUSDMATERIALWRITER_H_
