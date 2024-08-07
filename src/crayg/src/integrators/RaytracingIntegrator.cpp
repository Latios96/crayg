#include "RaytracingIntegrator.h"
#include "sampling/Sampling.h"

namespace crayg {

RaytracingIntegrator::RaytracingIntegrator(Scene &scene, const std::shared_ptr<SceneIntersector> &sceneIntersector,
                                           const IntegratorSettings &integratorSettings)
    : AbstractIntegrator(scene, sceneIntersector) {
    useGi = std::get<int>(integratorSettings.getOrDefault("RAYTRACING:useGi", {0})) == 1 ? true : false;
}

Color RaytracingIntegrator::integrate(const Ray &ray, int recursionDepth) {
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
    IntegratorContext integratorContext = createIntegratorContext(recursionDepth);
    Color shadedColor = object.getMaterial()->evaluate(surfaceInteraction, integratorContext);

    Color radiance = Color::createBlack();
    for (auto &light : scene.lights) {
        radiance = radiance + calculateDirectLight(light, location, normal);
    }

    Color gi = Color::createBlack();
    if (useGi) {
        gi = calculateIndirectLight(surfaceInteraction, object.getOrthonormalBasis(location), integratorContext);
    }

    return shadedColor * (radiance + gi); // FIXME: this is only correct for completly diffuse surfaces..
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

Color RaytracingIntegrator::calculateIndirectLight(const SurfaceInteraction &surfaceInteraction,
                                                   const OrthonormalBasis &orthonormalBasis,
                                                   IntegratorContext &integratorContext) {
    const Vector3f randomDirOnHemisphere = Sampling::uniformSampleHemisphere();
    const Vector3f giDir = orthonormalBasis.toLocalCoordinates(randomDirOnHemisphere);
    const Ray giRay = surfaceInteraction.spawnRayFromSurface(giDir);
    return integratorContext.integrateRay(giRay);
}
}