#include "RaytracingIntegrator.h"

namespace crayg {

RaytracingIntegrator::RaytracingIntegrator(Scene &scene, const std::shared_ptr<SceneIntersector> &sceneIntersector)
    : AbstractIntegrator(scene, sceneIntersector), lambertMethod({scene}) {
}

Color RaytracingIntegrator::integrate(const Ray &ray) {
    return integrate(ray, 0);
}
Color RaytracingIntegrator::integrate(const Ray &ray, int depth) {
    if (depth == MAX_DEPTH) {
        return Color::createBlack();
    }
    auto intersection = sceneIntersector->intersect(ray);

    const bool hasHit = intersection.imageable != nullptr;
    if (hasHit) {
        const Vector3f location = ray.constructIntersectionPoint(intersection.rayParameter);
        Imageable &object = *intersection.imageable;
        Color shadedColor;
        const Vector3f normal = object.getNormal(location);
        if (object.getMaterial()->getDiffuseColor() == Color(10, 10, 10)) {
            return Color::createWhite();
        }
        if (object.getMaterial()->reflectivity()) {
            Ray reflectedRay = Ray(location, ray.direction - normal * (2 * (ray.direction.scalarProduct(normal))));
            shadedColor = integrate(reflectedRay, depth + 1);
        } else {
            shadedColor = lambertMethod.lambertShading(location, object);
        }

        float shadow = 1.0;
        for (auto &light: scene.lights) {
            shadow = light->calculateShadowFactor(*sceneIntersector, location + (normal * 0.001));
        }
        return shadedColor * shadow;
    }
    return Color::createBlack();
}
}