#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_EXITPUPILCALCULATOR_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_EXITPUPILCALCULATOR_H_

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
                                 TaskReporter &taskReporter);
    ExitPupil calculate();

  private:
    Bounds2df calculateExitPupilForInterval(int intervalIndex);
    void calculateSerial(ExitPupil &exitPupil, BaseTaskReporter::TaskProgressController &progressController);
    void calculateParallel(ExitPupil &exitPupil, BaseTaskReporter::TaskProgressController &progressController);
    CameraLens &lens;
    float filmDiagonalLength;
    CalculationSettings calculationSettings;
    TaskReporter &taskReporter;
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_EXITPUPILCALCULATOR_H_
