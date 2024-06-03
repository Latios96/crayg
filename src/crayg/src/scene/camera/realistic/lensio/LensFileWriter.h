#pragma once

#include "scene/camera/realistic/CameraLens.h"
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
