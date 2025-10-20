#pragma once
#include "crayg/imaging/CameraLens.h"
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
