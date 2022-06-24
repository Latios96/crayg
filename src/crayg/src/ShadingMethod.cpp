#include "ShadingMethod.h"

namespace crayg {

Color ShadingMethod::lambertShading(Vector3f point, Imageable &object) {
    Vector3f normal = object.getNormal(point);

    Color lightConstribution = Color();

    for (const auto &light : scene.lights) {
        lightConstribution = lightConstribution + colorForLight(point, normal, light);
    }

    const Color &color = object.getMaterial()->getDiffuseColor();
    return lightConstribution * color;

}

Color ShadingMethod::colorForLight(const Vector3f &point,
                                   const Vector3f &normal,
                                   const std::shared_ptr<Light> &light) const {
    Color color = Color::createBlack();
    Vector3f lightVector = (light->getPosition() - point).normalize();

    float scalar = normal.scalarProduct(lightVector);
    float scalarWithLightIntensity = scalar * light->getIntensity();

    const bool scalarHasValidRange = scalarWithLightIntensity > 0;

    if (scalarHasValidRange) {
        color = color + scalarWithLightIntensity;
    }

    return color;
}

ShadingMethod::ShadingMethod(Scene &scene) : scene(scene) {}

}
