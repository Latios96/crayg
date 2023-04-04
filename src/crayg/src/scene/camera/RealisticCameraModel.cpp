#include "RealisticCameraModel.h"
#include "ExitPupilCalculator.h"
#include "Logger.h"
#include "sampling/Random.h"

namespace crayg {

RealisticCameraModel::RealisticCameraModel(Camera &camera, const Resolution &resolution)
    : CameraModel(camera, resolution) {
    const float aspectRatio = static_cast<float>(resolution.getWidth()) / static_cast<float>(resolution.getHeight());
    filmPhysicalExtend =
        Bounds2df({camera.getFilmbackSize() * 0.1f / 2.f, -camera.getFilmbackSize() * 0.1f / aspectRatio / 2},
                  {-camera.getFilmbackSize() * 0.1f / 2.f, camera.getFilmbackSize() * 0.1f / aspectRatio / 2});
}

void RealisticCameraModel::init() {
    camera.getLens().focusLens(camera.getFocusDistance());
    ;
    computeExitPupil();
}

void RealisticCameraModel::computeExitPupil() {
    ExitPupilCalculator::CalculationSettings calculationSettings;
    ExitPupilCalculator exitPupilCalculator(camera.getLens(), camera.getFilmbackSize(),
                                            calculationSettings); // todo proper film size
    exitPupil = exitPupilCalculator.calculate();
}

Ray RealisticCameraModel::createPrimaryRay(float x, float y) {
    const float relatixeX = x / resolution.getWidth();
    const float relatixeY = y / resolution.getHeight();
    const auto filmPos = filmPhysicalExtend.lerp(relatixeX, relatixeY);
    const Vector3f positionOnFilm = {filmPos.x, filmPos.y, 0};

    const auto pupilSample = exitPupil.samplePupil({x, y}, camera.getFilmbackSize());
    const auto pointOnPupil = Vector3f(pupilSample.x, pupilSample.y, camera.getLens().getLastElement().center);
    const Ray ray = {positionOnFilm, (pointOnPupil - positionOnFilm).normalize()};
    const auto tracedRay = camera.getLens().traceFromFilmToWorld(ray).value_or(Ray({0, 0, 0}, {0, 0, 0}));
    return {camera.getPosition() + tracedRay.startPoint,
            camera.getTransform().applyForNormal(tracedRay.direction).normalize()};
}

} // crayg