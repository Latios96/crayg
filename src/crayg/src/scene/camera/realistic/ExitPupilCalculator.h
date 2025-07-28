#pragma once

#include "CameraLens.h"
#include "ExitPupil.h"
#include "basics/Bound2d.h"
#include "utils/DtoUtils.h"
#include "utils/TaskReporter.h"
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
