#include "RealisticCameraModel.h"
#include "ExitPupilCalculator.h"

namespace crayg {

RealisticCameraModel::RealisticCameraModel(Camera &camera, const Resolution &resolution)
    : CameraModel(camera, resolution) {
    const float aspectRatio = static_cast<float>(resolution.getWidth()) / static_cast<float>(resolution.getHeight());
    filmPhysicalExtend =
        Bounds2df({camera.getFilmbackSize() * 0.1f / 2.f, -camera.getFilmbackSize() * 0.1f / aspectRatio / 2},
                  {-camera.getFilmbackSize() * 0.1f / 2.f, camera.getFilmbackSize() * 0.1f / aspectRatio / 2});
    filmDiagonal = std::sqrt(std::pow(camera.getFilmbackSize() * 0.1f, 2) +
                             std::pow(camera.getFilmbackSize() * 0.1f / aspectRatio, 2));
}

void RealisticCameraModel::init() {
    camera.getLens().focusLens(camera.getFocusDistance());

    const float focalLength = calculateEffectiveFocalLength(camera.getLens());
    const float apertureRadius = (focalLength / camera.getFStop()) / 2.0f;
    camera.getLens().getAperture().apertureRadius =
        std::max(apertureRadius, camera.getLens().getAperture().apertureRadius);

    ExitPupilCalculator exitPupilCalculator(camera.getLens(), filmDiagonal, ExitPupilCalculator::CalculationSettings());
    exitPupil = exitPupilCalculator.calculate();
}

std::optional<Ray> RealisticCameraModel::createPrimaryRay(float x, float y) {
    const float relatixeX = x / resolution.getWidth();
    const float relatixeY = y / resolution.getHeight();
    const auto filmPos = filmPhysicalExtend.lerp(relatixeX, relatixeY);
    const Vector3f positionOnFilm = {filmPos.x, filmPos.y, 0};

    const auto pupilSample = exitPupil.samplePupil(filmPos, filmDiagonal);
    const auto pointOnPupil = Vector3f(pupilSample.x, pupilSample.y, camera.getLens().getLastElement().center);
    const Ray ray = {positionOnFilm, (pointOnPupil - positionOnFilm).normalize()};
    const auto tracedRay = camera.getLens().traceFromFilmToWorld(ray);
    if (!tracedRay) {
        return std::nullopt;
    }
    return camera.getTransform().apply(*tracedRay);
}

} // crayg