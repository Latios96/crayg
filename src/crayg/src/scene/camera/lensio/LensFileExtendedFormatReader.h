#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_LENSIO_LENSFILEEXTENDEDFORMATREADER_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_LENSIO_LENSFILEEXTENDEDFORMATREADER_H_

#include "LensFileReader.h"

namespace crayg {

class LensFileExtendedFormatReader : public LensFileReader {
  public:
    explicit LensFileExtendedFormatReader() = default;
    CameraLens readFileContent(const std::string &content) override;

    CameraLensMetadata parseMetadata(const std::vector<std::string> &lines);
    std::vector<LensElement> parseElements(const std::vector<std::string> &lines);
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_LENSIO_LENSFILEEXTENDEDFORMATREADER_H_
