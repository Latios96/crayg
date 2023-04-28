#include "AmbientOcclusionIntegrator.h"
#include "sampling/Sampling.h"

namespace crayg {

AmbientOcclusionIntegrator::AmbientOcclusionIntegrator(Scene &scene,
                                                       const std::shared_ptr<SceneIntersector> &sceneIntersector,
                                                       const IntegratorSettings &integratorSettings)
    : AbstractIntegrator(scene, sceneIntersector) {
    sampleCount = std::get<int>(integratorSettings.getOrDefault("AMBIENT_OCCLUSION:sampleCount", {8}));
    radius = std::get<float>(integratorSettings.getOrDefault("AMBIENT_OCCLUSION:radius", {3.0f}));
}

Color AmbientOcclusionIntegrator::integrate(const Ray &ray, int recursionDepth) {
    auto intersection = sceneIntersector->intersect(ray);

    const bool hasHit = intersection.imageable != nullptr;
    if (!hasHit) {
        return Color::createBlack();
    }

    const Vector3f location = ray.constructIntersectionPoint(intersection.rayParameter);

    return calculateAmbientOcclusionAtPoint(intersection, location);
}

Color AmbientOcclusionIntegrator::calculateAmbientOcclusionAtPoint(Imageable::Intersection &intersection,
                                                                   const Vector3f &location) const {
    const auto orthonormalBasis = intersection.imageable->getOrthonormalBasis(location);

    int countClear = 0;
    for (int i = 0; i < sampleCount; i++) {
        Vector3f directionOnHemisphere = Sampling::uniformSampleHemisphere();
        Vector3f direction = orthonormalBasis.toLocalCoordinates(directionOnHemisphere);
        Ray aoRay(location, direction);
        const bool isOccluded = sceneIntersector->isOccluded(aoRay, radius);
        if (!isOccluded) {
            countClear++;
        }
    }
    return Color::createGrey(static_cast<float>(countClear) / static_cast<float>(sampleCount));
}

} // crayg