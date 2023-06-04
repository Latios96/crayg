#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_CAMERAUTILS_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_CAMERAUTILS_H_

namespace crayg {

class CameraUtils {
  public:
    static float computeApertureRadius(float focalLength_mm, float fStop);
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_CAMERAUTILS_H_
