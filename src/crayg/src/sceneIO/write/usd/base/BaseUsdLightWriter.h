#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_BASEUSDLIGHTWRITER_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_BASEUSDLIGHTWRITER_H_

#include "BaseUsdTransformableWriter.h"

namespace crayg {

template <class UsdType, class CraygType>
class BaseUsdLightWriter : public BaseUsdTransformableWriter<UsdType, CraygType> {
  public:
    BaseUsdLightWriter(CraygType &craygObject) : BaseUsdTransformableWriter<UsdType, CraygType>(craygObject) {
    }

    UsdType write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) override {
        auto light = BaseUsdTransformableWriter<UsdType, CraygType>::write(stage, usdPathFactory);

        light.GetIntensityAttr().Set(this->craygObject.getIntensity());
        light.GetColorAttr().Set(UsdConversions::convert(this->craygObject.getColor()));

        return light;
    }

  protected:
    std::string getTranslatedType() override {
        return this->craygObject.getType();
    }
};

}

#endif // CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_BASEUSDLIGHTWRITER_H_
