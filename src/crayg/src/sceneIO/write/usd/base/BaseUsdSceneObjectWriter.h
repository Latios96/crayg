#pragma once

#include "BaseUsdTransformableWriter.h"
#include "Logger.h"
#include "sceneIO/usd/CraygUsdBase.h"
#include "sceneIO/usd/UsdConversions.h"
#include "sceneIO/write/usd/UsdPathFactory.h"
#include "sceneIO/write/usd/shadingnetworks/caches/UsdMaterialWriteCache.h"
#include <memory>
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdShade/materialBindingAPI.h>

namespace crayg {

template <class UsdType, class CraygType>
class BaseUsdSceneObjectWriter : public BaseUsdTransformableWriter<UsdType, CraygType> {
  public:
    BaseUsdSceneObjectWriter(CraygType &craygObject, UsdMaterialWriteCache &usdMaterialWriteCache)
        : BaseUsdTransformableWriter<UsdType, CraygType>(craygObject), usdMaterialWriteCache(usdMaterialWriteCache) {
    }

    UsdType write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) override {
        auto usdObject = BaseUsdTransformableWriter<UsdType, CraygType>::write(stage, usdPathFactory);

        if (this->craygObject.getMaterial()) {
            auto material = usdMaterialWriteCache.getCachedUsdMaterial(this->craygObject.getMaterial());
            pxr::UsdShadeMaterialBindingAPI bindingApi(usdObject.GetPrim());
            bindingApi.Bind(material);
        }

        return usdObject;
    }

  protected:
    std::string getTranslatedType() override {
        return this->craygObject.getType();
    }

    UsdMaterialWriteCache &usdMaterialWriteCache;
};

}
