#include "UsdPreviewSurface.h"
#include "Logger.h"
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

void UsdPreviewSurface::getLobes(const SurfaceInteraction &surfaceInteraction, Lobes &lobes) {
    lobes.specular.weight = getReflectivity(surfaceInteraction);
    if (!lobes.specular.weight.isBlack()) {
        lobes.specular.sampleDirection = surfaceInteraction.spawnReflectionRayFromSurface();
    }

    lobes.diffuse.weight = (Color::createWhite() - lobes.specular.weight) * diffuseColor.evaluate(surfaceInteraction);
    if (!lobes.diffuse.weight.isBlack()) {
        const Vector3f randomDirOnHemisphere = Sampling::uniformSampleHemisphere();
        auto orthonormalBasis = surfaceInteraction.getOrthonormalBasis();
        const Vector3f giDir = orthonormalBasis.toLocalCoordinates(randomDirOnHemisphere);
        lobes.diffuse.sampleDirection = surfaceInteraction.spawnRayFromSurface(giDir);
    }
}

}