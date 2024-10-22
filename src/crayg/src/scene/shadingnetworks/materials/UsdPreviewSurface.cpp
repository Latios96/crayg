#include "UsdPreviewSurface.h"
#include "Logger.h"
#include "basics/MathUtils.h"
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

Vector3f roughReflect(const SurfaceInteraction &surfaceInteraction, float roughness) {
    const Vector3f perfectReflection = surfaceInteraction.ray.direction.reflect(surfaceInteraction.normal);

    if (roughness == 0) {
        return perfectReflection;
    }

    const Vector3f randomDirOnHemisphere = Sampling::uniformSampleHemisphere();
    auto orthonormalBasis = surfaceInteraction.getOrthonormalBasis();
    const Vector3f roughReflection = orthonormalBasis.toLocalCoordinates(randomDirOnHemisphere);
    return MathUtils::lerp(roughness * roughness, perfectReflection, roughReflection);
}

void UsdPreviewSurface::getLobes(const SurfaceInteraction &surfaceInteraction, Lobes &lobes) {
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
    }

    lobes.diffuse.weight = (Color::createWhite() - lobes.specular.weight * reflectance) * evaluatedDiffuse;
    if (!lobes.diffuse.weight.isBlack()) {
        const Vector3f randomDirOnHemisphere = Sampling::uniformSampleHemisphere();
        auto orthonormalBasis = surfaceInteraction.getOrthonormalBasis();
        const Vector3f giDir = orthonormalBasis.toLocalCoordinates(randomDirOnHemisphere);
        lobes.diffuse.sampleDirection = surfaceInteraction.spawnRayFromSurface(giDir);
    }
}

}