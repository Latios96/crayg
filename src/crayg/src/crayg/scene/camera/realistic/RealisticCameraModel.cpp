#include "RealisticCameraModel.h"
#include "ExitPupilCalculator.h"
#include "Wavelengths.h"
#include "crayg/foundation/logging/Logger.h"
#include "crayg/foundation/tracing/CraygTracing.h"
#include "crayg/renderer/sampling/Random.h"

namespace crayg {

RealisticCameraModel::RealisticCameraModel(Camera &camera, const Resolution &resolution)
    : CameraModel(camera, resolution) {
    const float aspectRatio = static_cast<float>(resolution.getWidth()) / static_cast<float>(resolution.getHeight());
    filmPhysicalExtend =
        Bounds2df({camera.getFilmbackSize() * 0.1f / 2.f, -camera.getFilmbackSize() * 0.1f / aspectRatio / 2},
                  {-camera.getFilmbackSize() * 0.1f / 2.f, camera.getFilmbackSize() * 0.1f / aspectRatio / 2});
    filmDiagonal = std::sqrt(std::pow<float>(camera.getFilmbackSize() * 0.1f, 2) +
                             std::pow<float>(camera.getFilmbackSize() * 0.1f / aspectRatio, 2));
}

void RealisticCameraModel::init(BaseTaskReporter &taskReporter) {
    CRAYG_TRACE_SCOPE("Renderer");
    Logger::info("Effective focal length: {:.2f}mm", camera.getLens().metadata.focalLength * 10);

    Logger::info("Request zooming to {}", camera.getFocalLength());
    camera.getLens().zoom(camera.getFocalLength());
    Logger::info("Zoomed to focal length: {:.2f}mm", camera.getLens().metadata.focalLength * 10);

    camera.getLens().focusLens(camera.getFocusDistance());
    camera.getLens().changeAperture(camera.getFStop());

    ExitPupilCalculator exitPupilCalculator(camera.getLens(), filmDiagonal, ExitPupilCalculator::CalculationSettings(),
                                            taskReporter);
    exitPupil = exitPupilCalculator.calculate();
}

RayWithWeight RealisticCameraModel::createPrimaryRay(const Vector2f &pixelPos, float wavelength) {
    const float relatixeX = pixelPos.x / resolution.getWidth();
    const float relatixeY = pixelPos.y / resolution.getHeight();
    const auto filmPos = filmPhysicalExtend.lerp(relatixeX, relatixeY);
    const Vector3f positionOnFilm = {filmPos.x, filmPos.y, 0};

    const auto pupilSample = exitPupil.samplePupil(filmPos, filmDiagonal);
    const auto pointOnPupil =
        Vector3f(pupilSample.point.x, pupilSample.point.y, camera.getLens().getLastSurface().center);
    const Ray ray = {positionOnFilm, (pointOnPupil - positionOnFilm).normalize()};
    const auto tracedRay = camera.getLens().traceFromFilmToWorld(ray, wavelength);
    if (!tracedRay) {
        return {std::nullopt, 0};
    }

    const float weight = pupilSample.sampleBoundsArea / exitPupil.pupilBounds[0].area();
    const Transform &transform = camera.getTransform();
    return {transform.apply(*tracedRay), weight};
}

}