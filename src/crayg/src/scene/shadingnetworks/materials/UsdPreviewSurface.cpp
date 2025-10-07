#include "UsdPreviewSurface.h"
#include "Logger.h"
#include "sampling/Random.h"
#include "sampling/Sampling.h"
#include "scene/Imageable.h"

namespace crayg {

UsdPreviewSurface::UsdPreviewSurface() {
}

UsdPreviewSurface::UsdPreviewSurface(const Color &diffuseColor) : Material(), diffuseColor(diffuseColor) {
}

UsdPreviewSurface::UsdPreviewSurface(const std::string &name) : Material(name) {
}

UsdPreviewSurface::UsdPreviewSurface(const std::string &name, const Color &diffuseColor)
    : Material(name), diffuseColor(diffuseColor) {
}

std::string UsdPreviewSurface::getType() const {
    return "UsdPreviewSurface";
}

ShadingNodeOutputType UsdPreviewSurface::getOutputType() {
    return ShadingNodeOutputType::COLOR;
}

Color UsdPreviewSurface::getReflectivity(const SurfaceInteraction &surfaceInteraction) {
    if (useSpecularWorkflow) {
        return specularColor.evaluate(surfaceInteraction);
    }
    return Color::createGrey(metallic.evaluate(surfaceInteraction));
}

float F_schlick(float ior, const Vector3f &view, const Vector3f &halfVector) {
    const float iorDiff = 1 - ior;
    const float iorSum = 1 + ior;
    const float F_0 = (iorDiff * iorDiff) / (iorSum * iorSum);
    const float oneMinus = 1.f - halfVector.dot(view);
    return F_0 + (1.f - F_0) * oneMinus * oneMinus * oneMinus * oneMinus * oneMinus;
}

Vector3f sampleGGX(float roughness) {
    const float alpha = roughness * roughness;

    const float xi1 = Random::random();
    const float xi2 = Random::random();

    const float theta_h = std::atan(alpha * std::sqrt(xi1 / (1.0f - xi1)));

    const float phi_h = 2.0f * M_PI * xi2;

    const float sinThetaH = std::sin(theta_h);
    const float h_x = sinThetaH * std::cos(phi_h);
    const float h_y = std::cos(theta_h);
    const float h_z = sinThetaH * std::sin(phi_h);

    return Vector3f(h_x, h_y, h_z).normalize();
}

Vector3f roughReflect(const SurfaceInteraction &surfaceInteraction, float roughness) {
    const Vector3f microfacetNormal = sampleGGX(roughness);
    auto orthonormalBasis = surfaceInteraction.getOrthonormalBasis();
    const Vector3f roughReflection = orthonormalBasis.toLocalCoordinates(microfacetNormal);
    return surfaceInteraction.ray.direction.reflect(roughReflection);
}

void UsdPreviewSurface::getLobes(const SurfaceInteraction &surfaceInteraction, Lobes &lobes) {
    lobes.emission.weight = emissiveColor.evaluate(surfaceInteraction);
    const Color evaluatedDiffuse = diffuseColor.evaluate(surfaceInteraction);
    const float evaluatedMetallic = metallic.evaluate(surfaceInteraction);

    if (evaluatedMetallic > 0.f) {
        lobes.metallic.weight = Color::createGrey(evaluatedMetallic) * evaluatedDiffuse;
        const float evaluatedRoughness = roughness.evaluate(surfaceInteraction);
        lobes.metallic.sampleDirection =
            surfaceInteraction.spawnRayFromSurface(roughReflect(surfaceInteraction, evaluatedRoughness));
    }

    if (evaluatedMetallic >= 1.f) {
        return;
    }

    lobes.specular.weight = specularColor.evaluate(surfaceInteraction) * (1.f - evaluatedMetallic);
    const Vector3f halfVector =
        (lobes.specular.sampleDirection.direction + surfaceInteraction.ray.direction).normalize();

    float reflectance = 0;
    if (!lobes.specular.weight.isBlack()) {
        const float evaluatedRoughness = roughness.evaluate(surfaceInteraction);
        lobes.specular.sampleDirection =
            surfaceInteraction.spawnRayFromSurface(roughReflect(surfaceInteraction, evaluatedRoughness));
        const float evaluatedIor = ior.evaluate(surfaceInteraction);
        reflectance = F_schlick(evaluatedIor, surfaceInteraction.ray.direction, halfVector);
        lobes.specular.weight = lobes.specular.weight * reflectance;
    }

    lobes.diffuse.weight = (Color::createWhite() - lobes.specular.weight) * evaluatedDiffuse;
    if (!lobes.diffuse.weight.isBlack()) {
        const Vector3f randomDirOnHemisphere = Sampling::uniformSampleHemisphere();
        auto orthonormalBasis = surfaceInteraction.getOrthonormalBasis();
        const Vector3f giDir = orthonormalBasis.toLocalCoordinates(randomDirOnHemisphere);
        lobes.diffuse.sampleDirection = surfaceInteraction.spawnRayFromSurface(giDir);
    }
}

}