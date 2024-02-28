#include "UsdPreviewSurface.h"

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

Color UsdPreviewSurface::evaluate(const SurfaceInteraction &surfaceInteraction, IntegratorContext &integratorContext) {
    const Color reflectivity = getReflectivity(surfaceInteraction);

    if (reflectivity.isBlack()) {
        return diffuseColor.evaluate(surfaceInteraction);
    }

    const Ray reflectionRay = surfaceInteraction.spawnReflectionRayFromSurface();
    return diffuseColor.evaluate(surfaceInteraction) + reflectivity * integratorContext.integrateRay(reflectionRay);
}

std::string UsdPreviewSurface::getType() const {
    return "UsdPreviewSurface";
}

ShadingNodeOutputType UsdPreviewSurface::getOutputType() {
    return COLOR;
}

Color UsdPreviewSurface::getReflectivity(const SurfaceInteraction &surfaceInteraction) {
    if (useSpecularWorkflow) {
        return specularColor.evaluate(surfaceInteraction);
    }
    return Color::createGrey(metallic.evaluate(surfaceInteraction));
}

}