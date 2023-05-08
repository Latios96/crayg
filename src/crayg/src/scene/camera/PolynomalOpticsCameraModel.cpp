#include "PolynomalOpticsCameraModel.h"
#include "Logger.h"
#include "ThickLensApproximation.h"
#include "polynomal/lens.h"
#include "sampling/Random.h"
#include "utils/Preconditions.h"

namespace crayg {

PolynomalOpticsCameraModel::PolynomalOpticsCameraModel(Camera &camera, const Resolution &resolution)
    : RealisticCameraModel(camera, resolution) {
}

void PolynomalOpticsCameraModel::init() {
    RealisticCameraModel::init();
    /*ThickLensApproximationCalculator thickLensCalculator(camera.getLens());
    auto thickLens = thickLensCalculator.calculate();

    const float focalLength = calculateEffectiveFocalLength(thickLens);
    Logger::info("Effective focal length: {:.2f}mm", focalLength * 10);

    const float z = -camera.getFocusDistance();
    const float c = (thickLens.secondCardinalPoints.pZ - z - thickLens.firstCardinalPoints.pZ) *
                    (thickLens.secondCardinalPoints.pZ - z - 4 * focalLength - thickLens.firstCardinalPoints.pZ);
    if (c < 0) {
        CRAYG_LOG_AND_THROW(fmt::format("Focal distance {} is too short for this lens", camera.getFocusDistance()));
    }

    sensorOffset = 0.5f * (thickLens.secondCardinalPoints.pZ - z + thickLens.firstCardinalPoints.pZ - sqrt(c));*/
}

std::optional<Ray> PolynomalOpticsCameraModel::createPrimaryRay(float x, float y) {
    const float relatixeX = x / resolution.getWidth();
    const float relatixeY = y / resolution.getHeight();
    const auto filmPos = filmPhysicalExtend.lerp(relatixeX, relatixeY);
    const Vector3f positionOnFilm = {filmPos.x, filmPos.y, -2};
    const auto pupilSample = exitPupil.samplePupil(filmPos, filmDiagonal);
    const auto pointOnPupil = Vector3f(pupilSample.x, pupilSample.y, camera.getLens().getLastElement().center);

    const Vector3f direction = (pointOnPupil - positionOnFilm).normalize();

    float scale = 1 /* / direction.z*/;
    float in[5] = {filmPos.x * 10, filmPos.y * 10, direction.x * scale, direction.y * scale, 0.4};
    float out[5] = {0};

    // propagate ray from sensor to outer lens element
    double transmittance = lens_evaluate(in, out);

    if (transmittance <= 0) {
        return std::nullopt;
    }

    float cs_origin[3] = {0};
    float cs_direction[3] = {0};
    lens_sphereToCs(out, out + 2, cs_origin, cs_direction, -lens_outer_pupil_curvature_radius,
                    lens_outer_pupil_curvature_radius);

    /*auto realisticCameraModelRay = RealisticCameraModel::createPrimaryRay(x,y);
    return realisticCameraModelRay;*/

    const Ray &polynomalRay = Ray({cs_origin[0] / 10.f, cs_origin[1] / 10.f, cs_origin[2] /*lens_length / 10.f*/},
                                  Vector3f(cs_direction[0], cs_direction[1], cs_direction[2]));
    return camera.getTransform().apply(polynomalRay);
}

} // crayg