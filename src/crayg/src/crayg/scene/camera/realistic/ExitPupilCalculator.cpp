#include "ExitPupilCalculator.h"
#include "Wavelengths.h"
#include "crayg/foundation/math/CommonMath.h"
#include "crayg/foundation/progress/StopWatch.h"
#include "crayg/foundation/tracing/CraygTracing.h"
#include "crayg/renderer/sampling/Random.h"
#include <tbb/parallel_for.h>

namespace crayg {
ExitPupilCalculator::ExitPupilCalculator(CameraLens &lens, float filmDiagonalLength, const CalculationSettings &samples,
                                         BaseTaskReporter &taskReporter)
    : lens(lens), filmDiagonalLength(filmDiagonalLength), calculationSettings(samples), taskReporter(taskReporter) {
}

ExitPupil ExitPupilCalculator::calculate() {
    CRAYG_TRACE_SCOPE("RealisticCamera");
    ExitPupil exitPupil;
    exitPupil.pupilBounds.resize(calculationSettings.samplesFilmX);

    auto progressController = taskReporter.startTask("Computing exit pupil", calculationSettings.samplesFilmX);

    if (calculationSettings.serial) {
        calculateSerial(exitPupil, progressController);
    } else {
        calculateParallel(exitPupil, progressController);
    }

    progressController.finish();

    return exitPupil;
}

void ExitPupilCalculator::calculateSerial(ExitPupil &exitPupil,
                                          BaseTaskReporter::TaskProgressController &progressController) {
    for (int i = 0; i < calculationSettings.samplesFilmX; i++) {
        exitPupil.pupilBounds[i] = calculateExitPupilForInterval(i);
        progressController.iterationDone();
    }
}

void ExitPupilCalculator::calculateParallel(ExitPupil &exitPupil,
                                            BaseTaskReporter::TaskProgressController &progressController) {
    tbb::parallel_for(0, calculationSettings.samplesFilmX, [this, &exitPupil, &progressController](int i) {
        exitPupil.pupilBounds[i] = calculateExitPupilForInterval(i);
        progressController.iterationDone();
    });
}

Bounds2df ExitPupilCalculator::calculateExitPupilForInterval(int intervalIndex) {
    const int maxSamples = calculationSettings.samplesLens * calculationSettings.samplesLens;
    const float filmIntervalStart = static_cast<float>(intervalIndex) /
                                    static_cast<float>(calculationSettings.samplesFilmX) * (filmDiagonalLength / 2.f);
    const float filmIntervalEnd = static_cast<float>(intervalIndex + 1) /
                                  static_cast<float>(calculationSettings.samplesFilmX) * (filmDiagonalLength / 2.f);

    const float rearApertureRadius = lens.getLastSurface().apertureRadius;
    const Bounds2df rearSurfaceExtend =
        Bounds2df(Vector2f(-1.5f * rearApertureRadius), Vector2f(1.5f * rearApertureRadius));

    Bounds2df pupilBounds;
    int exitingRays = 0;
    for (int sampleIndex = 0; sampleIndex < maxSamples; sampleIndex++) {
        const float filmX = CommonMath::lerp(static_cast<float>(sampleIndex) / static_cast<float>(maxSamples),
                                             filmIntervalStart, filmIntervalEnd);
        const Vector3f positionOnFilm = {filmX, 0, 0};
        const Vector2f posOnExtend = rearSurfaceExtend.lerp(Random::random(), Random::random());
        const Vector3f positionOnRearExtend(posOnExtend.x, posOnExtend.y, lens.getLastSurface().center);

        const bool positionOnLensIsAlreadyInBounds = pupilBounds.contains(posOnExtend);
        if (!positionOnLensIsAlreadyInBounds) {
            const Ray ray(positionOnFilm, (positionOnRearExtend - positionOnFilm).normalize());
            auto resultingRay = lens.traceFromFilmToWorld(ray, FraunhoferLines::SODIUM.wavelength);
            if (resultingRay) {
                pupilBounds = pupilBounds.unionWith(posOnExtend);
                exitingRays++;
            }
        }
    }
    if (!exitingRays) {
        return rearSurfaceExtend;
    }
    const float delta = 2 * rearSurfaceExtend.diagonal().length() / calculationSettings.samplesLens;
    pupilBounds = Bounds2df({pupilBounds.min.x - delta, pupilBounds.min.y - delta},
                            {pupilBounds.max.x + delta, pupilBounds.max.y + delta});

    return pupilBounds;
}

}