#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_LENSIO_LENSFILEREADERFACTORY_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_LENSIO_LENSFILEREADERFACTORY_H_

#include "LensFileReader.h"
#include "LensFileTextFileReader.h"

namespace crayg {

class LensFileReaderFactory {
  public:
    static std::unique_ptr<LensFileReader> createLensFileReader(const std::string &filePath);
};
} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_LENSIO_LENSFILEREADERFACTORY_H_
