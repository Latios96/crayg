#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_LENSIO_LENSFILEWRITER_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_LENSIO_LENSFILEWRITER_H_

#include "scene/camera/CameraLens.h"
#include <string>

namespace crayg {

class LensFileWriter {
  public:
    virtual void writeFile(const std::string &filePath, const CameraLens &cameraLens);

    virtual std::string writeFileContent(const CameraLens &cameraLens) = 0;

    virtual ~LensFileWriter() = default;

  protected:
    std::string filePath;
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_LENSIO_LENSFILEWRITER_H_
