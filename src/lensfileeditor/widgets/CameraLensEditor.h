#pragma once
#include "scene/camera/realistic/CameraLens.h"
#include <QWidget>

namespace crayg {

class CameraLensEditor : public QWidget {
    Q_OBJECT
  public:
    CameraLensEditor();

  private:
    void setupUI();
    std::unique_ptr<CameraLens> cameraLens;
};

}
