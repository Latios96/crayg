#include "UsdSphereLightReader.h"
#include "crayg/foundation/logging/Logger.h"
#include "scene/io/usd/UsdConversions.h"
#include "scene/io/usd/UsdReadUtils.h"
#include "scene/io/usd/UsdUtils.h"

namespace crayg {

UsdSphereLightReader::UsdSphereLightReader(const pxr::UsdLuxSphereLight &sphereLight)
    : BaseUsdLightReader(sphereLight) {
}

std::shared_ptr<Light> UsdSphereLightReader::read() {
    auto light = BaseUsdLightReader<pxr::UsdLuxSphereLight, Light>::read();

    return light;
}

std::string UsdSphereLightReader::getTranslatedType() {
    return "sphereLight";
}

}
