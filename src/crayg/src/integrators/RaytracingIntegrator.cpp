#include "RaytracingIntegrator.h"
#include "Logger.h"
#include "sampling/Sampling.h"

namespace crayg {

RaytracingIntegrator::RaytracingIntegrator(Scene &scene, const std::shared_ptr<SceneIntersector> &sceneIntersector,
                                           const IntegratorSettings &integratorSettings)
    : AbstractIntegrator(scene, sceneIntersector) {
    useGi = std::get<int>(integratorSettings.getOrDefault("RAYTRACING:useGi", {0})) == 1 ? true : false;
}

Color RaytracingIntegrator::integrate(const Ray &ray, int recursionDepth, RayType rayType) {
    if (recursionDepth == RaytracingIntegrator::MAX_RECURSION_DEPTH) {
        return Color::createBlack();
    }
    thread_local HitStorage hitStorage;
    auto intersection = sceneIntersector->intersect(ray, hitStorage);

    const bool hasHit = intersection.imageable != nullptr;
    if (!hasHit) {
        return Color::createBlack();
    }

    const Vector3f location = ray.constructIntersectionPoint(intersection.rayParameter);
    Imageable &object = *intersection.imageable;
    const Vector3f normal = object.getNormal(location);
    const SurfaceInteraction surfaceInteraction = SurfaceInteraction(object, location, normal, ray);

    Color radiance = Color::createBlack();
    for (auto &light : scene.lights) {
        radiance = radiance + calculateDirectLight(light, location, normal);
    }

    Lobes lobes;
    object.getMaterial()->getLobes(surfaceInteraction, lobes);

    Color lobesResult = Color::createBlack();
    int contributingLobes = 0;

    if (!lobes.emission.weight.isBlack()) {
        lobesResult += lobes.emission.weight;
        contributingLobes++;
    }

    if (!lobes.metallic.weight.isBlack()) {
        lobesResult +=
            lobes.metallic.weight * integrate(lobes.metallic.sampleDirection, recursionDepth + 1, RayType::SPECULAR);
        contributingLobes++;
    }

    if (!lobes.specular.weight.isBlack()) {
        lobesResult +=
            lobes.specular.weight * integrate(lobes.specular.sampleDirection, recursionDepth + 1, RayType::SPECULAR);
        contributingLobes++;
    }

    if (!lobes.diffuse.weight.isBlack()) {
        const Color indirectLight = useGi
                                        ? integrate(lobes.diffuse.sampleDirection, recursionDepth + 1, RayType::DIFFUSE)
                                        : Color::createBlack();
        lobesResult += lobes.diffuse.weight * (radiance + indirectLight);
        contributingLobes++;
    }

    if (contributingLobes) {
        lobesResult = lobesResult / static_cast<float>(contributingLobes);
    }

    return lobesResult;
}

Color RaytracingIntegrator::calculateDirectLight(std::shared_ptr<Light> &light, const Vector3f &location,
                                                 const Vector3f &normal) {
    auto lightRadiance = light->radiance(location + (normal * 0.001f), normal);
    if (lightRadiance.radiance == Color::createBlack()) {
        return Color::createBlack();
    }
    float angle = normal.dot(lightRadiance.ray.direction.normalize());
    if (angle <= 0) {
        return Color::createBlack();
    }

    Ray rayToTrace = {lightRadiance.ray.startPoint, lightRadiance.ray.direction.normalize()};
    thread_local HitStorage hitStorage;
    const bool lightIsOccluded =
        sceneIntersector->isOccluded(rayToTrace, hitStorage, lightRadiance.ray.direction.length());

    if (lightIsOccluded) {
        return Color::createBlack();
    }

    return lightRadiance.radiance;
}

}