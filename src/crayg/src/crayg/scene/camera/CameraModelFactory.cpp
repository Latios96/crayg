#include "CameraModelFactory.h"

#include "crayg/scene/camera/pinhole/PinholeCameraModel.h"
#include "crayg/scene/camera/realistic/RealisticCameraModel.h"
#include "crayg/scene/camera/thinlens/ThinLensCameraModel.h"

namespace crayg {
std::unique_ptr<CameraModel> CameraModelFactory::createCameraModel(Camera &camera, const Resolution &resolution) {
    switch (camera.getCameraType()) {
    case CameraType::PINHOLE:
        return std::make_unique<PinholeCameraModel>(camera, resolution);
    case CameraType::THIN_LENS:
        return std::make_unique<ThinLensCameraModel>(camera, resolution);
    case CameraType::REALISTIC:
        return std::make_unique<RealisticCameraModel>(camera, resolution);
    default:
        CRAYG_LOG_AND_THROW_RUNTIME_ERROR(R"(Unsupported CameraType: "{}")", camera.getCameraType());
    }
}
}