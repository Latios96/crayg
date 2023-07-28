#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_LENSIO_LENSFILEJSONREADER_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_LENSIO_LENSFILEJSONREADER_H_

#include "scene/camera/realistic/lensio/LensFileReader.h"

namespace crayg {

class LensFileJsonReader : public LensFileReader {
  public:
    CameraLens readFileContent(const std::string &content) override;
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_LENSIO_LENSFILEJSONREADER_H_
