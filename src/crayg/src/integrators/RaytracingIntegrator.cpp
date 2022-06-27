#include "RaytracingIntegrator.h"

namespace crayg {

RaytracingIntegrator::RaytracingIntegrator(Scene &scene, const std::shared_ptr<SceneIntersector> &sceneIntersector)
    : AbstractIntegrator(scene, sceneIntersector), lambertMethod({scene}) {
}

Color RaytracingIntegrator::integrate(const Ray &ray) {
    return integrate(ray, 0);
}
Color RaytracingIntegrator::integrate(const Ray &ray, int depth) {
    auto intersection = sceneIntersector->intersect(ray);

    const bool hasHit = intersection.imageable != nullptr;
    if (!hasHit) {
        return Color::createBlack();
    }

    const Vector3f location = ray.constructIntersectionPoint(intersection.rayParameter);
    Imageable &object = *intersection.imageable;
    Color shadedColor = object.getMaterial()->getDiffuseColor();
    const Vector3f normal = object.getNormal(location);

    Color radiance = Color::createBlack();
    for (auto &light: scene.lights) {
        radiance = radiance + calculateDirectLight(light, location, normal);
    }
    return shadedColor * radiance;
}

Color RaytracingIntegrator::calculateDirectLight(std::shared_ptr<Light> &light,
                                                 const Vector3f &location,
                                                 const Vector3f &normal) {
    auto lightRadiance = light->radiance(location + (normal * 0.001), normal);
    if (lightRadiance.radiance == Color::createBlack()) {
        return Color::createBlack();
    }
    float angle = normal.scalarProduct(lightRadiance.ray.direction.normalize());
    if (angle <= 0) {
        return Color::createBlack();
    }

    Ray rayToTrace = {lightRadiance.ray.startPoint, lightRadiance.ray.direction.normalize()};
    auto intersection = sceneIntersector->intersect(rayToTrace);

    if (intersection.imageable == nullptr) {
        return lightRadiance.radiance;
    }

    bool lightIsHidden = intersection.rayParameter <= lightRadiance.ray.direction.length();
    if (lightIsHidden) {
        return Color::createBlack();
    }

    return lightRadiance.radiance;
}
}