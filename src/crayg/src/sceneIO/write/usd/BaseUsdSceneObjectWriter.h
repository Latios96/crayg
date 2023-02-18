#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_BASEUSDSCENEOBJECTWRITER_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_BASEUSDSCENEOBJECTWRITER_H_

#include <memory>
#include "Logger.h"
#include "sceneIO/usd/CraygUsdBase.h"
#include "UsdPathFactory.h"
#include "BaseUsdTransformableWriter.h"
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdShade/materialBindingAPI.h>
#include "sceneIO/usd/UsdConversions.h"
#include "sceneIO/write/usd/UsdMaterialWriteCache.h"

namespace crayg {

template<class UsdType, class CraygType>
class BaseUsdSceneObjectWriter : public BaseUsdTransformableWriter<UsdType, CraygType> {
 public:
    BaseUsdSceneObjectWriter(CraygType &craygObject,
                             UsdMaterialWriteCache &usdMaterialWriteCache) : BaseUsdTransformableWriter<UsdType,
                                                                                                        CraygType>(
        craygObject), usdMaterialWriteCache(usdMaterialWriteCache) {}

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

} // crayg

#endif //CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_BASEUSDSCENEOBJECTWRITER_H_
