#include "UsdSphereLightReader.h"
#include "sceneIO/usd/UsdConversions.h"
#include "sceneIO/usd/UsdReadUtils.h"
#include "sceneIO/usd/UsdUtils.h"
#include "Logger.h"

namespace crayg {

UsdSphereLightReader::UsdSphereLightReader(const pxr::UsdLuxSphereLight &sphereLight)
    : BaseUsdLightReader(sphereLight) {}

std::shared_ptr<Light> UsdSphereLightReader::read() {
    auto light = BaseUsdLightReader<pxr::UsdLuxSphereLight, Light>::read();

    return light;
}
std::string UsdSphereLightReader::getTranslatedType() {
    return "sphereLight";
}

}

