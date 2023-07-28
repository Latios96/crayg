#include "ExitPupilCalculator.h"
#include "basics/MathUtils.h"
#include "sampling/Random.h"
#include "utils/StopWatch.h"
#include <tbb/parallel_for.h>

namespace crayg {
ExitPupilCalculator::ExitPupilCalculator(CameraLens &lens, float filmDiagonalLength, const CalculationSettings &samples,
                                         TaskReporter &taskReporter)
    : lens(lens), filmDiagonalLength(filmDiagonalLength), calculationSettings(samples), taskReporter(taskReporter) {
}

ExitPupil ExitPupilCalculator::calculate() {
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

    const float rearApertureRadius = lens.getLastElement().apertureRadius;
    const Bounds2df rearElementExtend =
        Bounds2df(Vector2f(-1.5f * rearApertureRadius), Vector2f(1.5f * rearApertureRadius));

    Bounds2df pupilBounds;
    int exitingRays = 0;
    for (int sampleIndex = 0; sampleIndex < maxSamples; sampleIndex++) {
        const float filmX = MathUtils::lerp(static_cast<float>(sampleIndex) / static_cast<float>(maxSamples),
                                            filmIntervalStart, filmIntervalEnd);
        const Vector3f positionOnFilm = {filmX, 0, 0};
        const Vector2f posOnExtend = rearElementExtend.lerp(Random::random(), Random::random());
        const Vector3f positionOnRearExtend(posOnExtend.x, posOnExtend.y, lens.getLastElement().center);

        const bool positionOnLensIsAlreadyInBounds = pupilBounds.contains(posOnExtend);
        if (!positionOnLensIsAlreadyInBounds) {
            const Ray ray(positionOnFilm, (positionOnRearExtend - positionOnFilm).normalize());
            auto resultingRay = lens.traceFromFilmToWorld(ray);
            if (resultingRay) {
                pupilBounds = pupilBounds.unionWith(posOnExtend);
                exitingRays++;
            }
        }
    }
    if (!exitingRays) {
        return rearElementExtend;
    }

    const float delta = (4.5f * rearApertureRadius) / calculationSettings.samplesLens;
    pupilBounds = Bounds2df({pupilBounds.min.x - delta, pupilBounds.min.y - delta},
                            {pupilBounds.max.x + delta, pupilBounds.max.y + delta});

    return pupilBounds;
}

Vector2f ExitPupil::samplePupil(const Vector2f &filmPos, float filmDiagonal) const {
    const float distanceFromFilmCenter = filmPos.length();
    int boundsIndex = distanceFromFilmCenter / (filmDiagonal / 2) * pupilBounds.size();
    boundsIndex = std::min<int>(pupilBounds.size() - 1, boundsIndex);
    const auto pupil = pupilBounds[boundsIndex];

    const float sinTheta = (distanceFromFilmCenter != 0) ? filmPos.y / distanceFromFilmCenter : 0;
    const float cosTheta = (distanceFromFilmCenter != 0) ? filmPos.x / distanceFromFilmCenter : 1;
    auto pLens = pupil.lerp(Random::random(), Random::random());
    return {cosTheta * pLens.x - sinTheta * pLens.y, sinTheta * pLens.x + cosTheta * pLens.y};
}
} // crayg