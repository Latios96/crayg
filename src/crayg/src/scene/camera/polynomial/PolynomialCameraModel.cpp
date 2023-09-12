#include "PolynomialCameraModel.h"
#include "PolynomialLenses.h"
#include "lens.h"
#include "sampling/Sampling.h"
#include "scene/camera/CameraUtils.h"

namespace crayg {
PolynomialCameraModell::PolynomialCameraModell(Camera &camera, const Resolution &resolution)
    : CameraModel(camera, resolution) {
    const float aspectRatio = static_cast<float>(resolution.getWidth()) / static_cast<float>(resolution.getHeight());
    filmPhysicalExtend =
        Bounds2df({camera.getFilmbackSize() * 0.1f / 2.f, -camera.getFilmbackSize() * 0.1f / aspectRatio / 2},
                  {-camera.getFilmbackSize() * 0.1f / 2.f, camera.getFilmbackSize() * 0.1f / aspectRatio / 2});
}

void PolynomialCameraModell::init(BaseTaskReporter &taskReporter) {
    CameraModel::init(taskReporter);
}

RayWithWeight PolynomialCameraModell::createPrimaryRay(float x, float y, float wavelength) {
    const float polynomialOffset = 0;
    if (!camera.getPolynomialLens()) {
        // throw std::runtime_error("No polynomial lens was set! Please specify a polynomial lens on the camera.");
    }
    PolynomialLens polynomialLens = *camera.getPolynomialLens();
    const float relatixeX = x / resolution.getWidth();
    const float relatixeY = y / resolution.getHeight();
    const auto filmPos = filmPhysicalExtend.lerp(relatixeX, relatixeY);

    float sensor[5] = {0};
    float aperture[5] = {0};
    float out[5] = {0};

    sensor[0] = filmPos.x * 10;
    sensor[1] = filmPos.y * 10;
    sensor[2] = 0;
    sensor[3] = 0;
    sensor[4] = wavelength / 1000.f;

    const auto apertureSample = Sampling::concentricSampleDisk() *
                                CameraUtils::computeApertureRadius(getFocalLength(polynomialLens), camera.getFStop());

    aperture[0] = apertureSample.x;
    aperture[1] = apertureSample.y;

    lens_pt_sample_aperture(sensor, aperture, polynomialOffset, polynomialLens); // todo support polynomial offset

    sensor[0] += sensor[2] * polynomialOffset;
    sensor[1] += sensor[3] * polynomialOffset;

    const float transmittance = lens_evaluate(sensor, out, polynomialLens);
    if (transmittance <= 0) {
        return {std::nullopt, 0};
    }

    // crop out by outgoing pupil
    const float outerPupilRadius = getOuterPupilRadius(polynomialLens);
    if (out[0] * out[0] + out[1] * out[1] > outerPupilRadius * outerPupilRadius) {
        return {std::nullopt, 0};
    }

    // crop at inward facing pupil
    const float focalLength = getFocalLength(polynomialLens);
    const double px = sensor[0] + sensor[2] * focalLength;
    const double py = sensor[1] + sensor[3] * focalLength; //(note that lens_back_focal_length is the back focal
                                                           // length, i.e. the distance unshifted sensor -> pupil)
    const float lensInnerPupilRadius = getInnerPupilRadius(polynomialLens);
    if (px * px + py * py > lensInnerPupilRadius * lensInnerPupilRadius) {
        return {std::nullopt, 0};
    }

    float cs_origin[3] = {0};
    float cs_direction[3] = {0};
    const float lens_outer_pupil_curvature_radius = getOuterPupilCurvatureRadius(polynomialLens);
    lens_sphereToCs(out, out + 2, cs_origin, cs_direction, -lens_outer_pupil_curvature_radius,
                    lens_outer_pupil_curvature_radius);

    const Ray &polynomalRay = Ray({cs_origin[0] / 10.f, cs_origin[1] / 10.f, cs_origin[2]},
                                  Vector3f(cs_direction[0], cs_direction[1], cs_direction[2]));

    return {camera.getTransform().apply(polynomalRay), 1};
}
} // crayg