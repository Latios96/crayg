#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_LENSIO_LENSFILEJSONWRITER_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_LENSIO_LENSFILEJSONWRITER_H_

#include "LensFileWriter.h"

namespace crayg {

class LensFileJsonWriter : public LensFileWriter {
  public:
    std::string writeFileContent(const CameraLens &cameraLens) override;
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_LENSIO_LENSFILEJSONWRITER_H_
