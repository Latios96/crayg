#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_LENSIO_LENSFILE_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_LENSIO_LENSFILE_H_

#include "scene/camera/CameraLens.h"
#include <sstream>
#include <string>
#include <vector>

namespace crayg {

class LensFileReader {
  public:
    explicit LensFileReader(const std::string &filePath);

    virtual CameraLens readFile();

    virtual CameraLens readFileContent(const std::string &content) = 0;

    virtual ~LensFileReader() = default;

  protected:
    std::string filePath;
};

}

#endif // CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_LENSIO_LENSFILE_H_
