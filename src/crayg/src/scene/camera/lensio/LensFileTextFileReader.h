#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_LENSIO_LENSFILETEXTFILEREADER_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_LENSIO_LENSFILETEXTFILEREADER_H_

#include "LensFileReader.h"

namespace crayg {

class LensFileTextFileReader : public LensFileReader {
  public:
    explicit LensFileTextFileReader(const std::string &filePath);
    CameraLens readFileContent(const std::string &content) override;

  private:
    LensElement readLensElement(const std::string &line) const;
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_LENSIO_LENSFILETEXTFILEREADER_H_
