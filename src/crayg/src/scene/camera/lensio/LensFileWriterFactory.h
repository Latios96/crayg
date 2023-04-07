#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_LENSIO_LENSFILEWRITERFACTORY_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_LENSIO_LENSFILEWRITERFACTORY_H_

#include "LensFileFormat.h"
#include "LensFileWriter.h"
#include <memory>
#include <string>

namespace crayg {

class LensFileWriterFactory {
  public:
    static std::unique_ptr<LensFileWriter> createLensFileWriter(const std::string &filePath);
    static std::unique_ptr<LensFileWriter> createLensFileWriter(LensFileFormat lensFileFormat);
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_LENSIO_LENSFILEWRITERFACTORY_H_
