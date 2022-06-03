//
// Created by Jan on 03.06.2022.
//

#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_BASEUSDLIGHTWRITER_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_BASEUSDLIGHTWRITER_H_

#include "BaseUsdTransformableWriter.h"

namespace crayg {

template<class UsdType, class CraygType>
class BaseUsdLightWriter : public BaseUsdTransformableWriter<UsdType, CraygType> {
 public:
    BaseUsdLightWriter(const std::shared_ptr<CraygType> &craygObject) : BaseUsdTransformableWriter<UsdType, CraygType>(
        craygObject) {}

    UsdType write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) override {
        auto light = BaseUsdTransformableWriter::write(stage, usdPathFactory);

        light.GetIntensityAttr().Set(this->craygObject->getIntensity());

        return light;
    }
 protected:
    std::string getTranslatedType() override {
        return this->craygObject->getType();
    }
};

}

#endif //CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_BASEUSDLIGHTWRITER_H_
