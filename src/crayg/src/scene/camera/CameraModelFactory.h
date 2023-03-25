#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_CAMERAMODELFACTORY_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_CAMERAMODELFACTORY_H_
#include "Camera.h"
#include "CameraModel.h"
#include "basics/Resolution.h"
#include <memory>

namespace crayg {

class CameraModelFactory {
  public:
    static std::unique_ptr<CameraModel> createCameraModel(Camera &camera, const Resolution &resolution);
};
} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_CAMERAMODELFACTORY_H_
