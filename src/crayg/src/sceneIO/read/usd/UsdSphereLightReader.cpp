#include "UsdSphereLightReader.h"
#include "sceneIO/usd/UsdConversions.h"
#include "sceneIO/usd/UsdReadUtils.h"
#include "sceneIO/usd/UsdUtils.h"
#include "Logger.h"

namespace crayg {

UsdSphereLightReader::UsdSphereLightReader(const pxr::UsdLuxSphereLight &sphereLight)
    : BaseUsdXformableReader(sphereLight) {}

std::shared_ptr<Light> UsdSphereLightReader::read() {
    auto light = BaseUsdXformableReader<pxr::UsdLuxSphereLight, Light>::read();

    const auto intensity = UsdUtils::getAttributeValueAs<float>(usdPrim.GetIntensityAttr());
    light->setIntensity(intensity);

    return light;
}
std::string UsdSphereLightReader::getTranslatedType() {
    return "sphereLight";
}

}

