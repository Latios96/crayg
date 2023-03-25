#include "CameraModelFactory.h"

#include "PineHoleCameraModel.h"
#include "ThinLensCameraModel.h"

namespace crayg {
std::unique_ptr<CameraModel> CameraModelFactory::createCameraModel(Camera &camera, const Resolution &resolution) {
    switch (camera.getCameraType()) {
    case CameraType::PINE_HOLE:
        return std::make_unique<PineHoleCameraModel>(camera, resolution);
    case CameraType::THIN_LENS:
        return std::make_unique<ThinLensCameraModel>(camera, resolution);
    default:
        throw std::runtime_error(fmt::format(R"(Unsupported CameraType: "{}")", camera.getCameraType()));
    }
}
} // crayg