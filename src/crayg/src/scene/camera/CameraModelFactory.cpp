#include "CameraModelFactory.h"

#include "scene/camera/pinehole/PineHoleCameraModel.h"
#include "scene/camera/polynomial/PolynomialCameraModel.h"
#include "scene/camera/realistic/RealisticCameraModel.h"
#include "scene/camera/thinlens/ThinLensCameraModel.h"

namespace crayg {
std::unique_ptr<CameraModel> CameraModelFactory::createCameraModel(Camera &camera, const Resolution &resolution) {
    switch (camera.getCameraType()) {
    case CameraType::PINE_HOLE:
        return std::make_unique<PineHoleCameraModel>(camera, resolution);
    case CameraType::THIN_LENS:
        return std::make_unique<ThinLensCameraModel>(camera, resolution);
    case CameraType::REALISTIC:
        return std::make_unique<RealisticCameraModel>(camera, resolution);
    case CameraType::POLYNOMIAL:
        return std::make_unique<PolynomialCameraModel>(camera, resolution);
    case CameraType::RAY_LUT:
        return std::make_unique<RealisticCameraModel>(camera, resolution);
    default:
        throw std::runtime_error(fmt::format(R"(Unsupported CameraType: "{}")", camera.getCameraType()));
    }
}
} // crayg