#pragma once

#include "CameraLens.h"
#include "ExitPupil.h"
#include "crayg/foundation/math/geometry/Bound2d.h"
#include "crayg/foundation/objects/DtoUtils.h"
#include "crayg/foundation/progress/TaskReporter.h"
#include <array>

namespace crayg {

class ExitPupilCalculator {
  public:
    struct CalculationSettings {
        int samplesFilmX = 64;
        int samplesLens = 1024;
        bool serial = false;
    };

    explicit ExitPupilCalculator(CameraLens &lens, float filmDiagonalLength, const CalculationSettings &samples,
                                 BaseTaskReporter &taskReporter);
    ExitPupil calculate();

  private:
    Bounds2df calculateExitPupilForInterval(int intervalIndex);
    void calculateSerial(ExitPupil &exitPupil, BaseTaskReporter::TaskProgressController &progressController);
    void calculateParallel(ExitPupil &exitPupil, BaseTaskReporter::TaskProgressController &progressController);
    CameraLens &lens;
    float filmDiagonalLength;
    CalculationSettings calculationSettings;
    BaseTaskReporter &taskReporter;
};

}
