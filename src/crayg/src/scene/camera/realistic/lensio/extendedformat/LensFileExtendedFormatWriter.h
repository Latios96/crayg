#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_LENSIO_LENSFILEEXTENDEDFORMATWRITER_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_LENSIO_LENSFILEEXTENDEDFORMATWRITER_H_

#include "scene/camera/realistic/lensio/LensFileWriter.h"

namespace crayg {

class LensFileExtendedFormatWriter : public LensFileWriter {
  public:
    std::string writeFileContent(const CameraLens &cameraLens) override;
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_LENSIO_LENSFILEEXTENDEDFORMATWRITER_H_
