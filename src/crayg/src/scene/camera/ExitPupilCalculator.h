#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_EXITPUPILCALCULATOR_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_EXITPUPILCALCULATOR_H_
#include "CameraLens.h"
#include "basics/Bound2d.h"
#include "utils/TaskReporter.h"
#include <array>

namespace crayg {

struct ExitPupil {
    std::vector<Bounds2df> pupilBounds;

    Vector2f samplePupil(const Vector2f &filmPos, float filmDiagonal) const;
};

class ExitPupilCalculator {
  public:
    struct CalculationSettings {
        int samplesFilmX = 128;
        int samplesLens = 2048;
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
