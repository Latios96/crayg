#include "UsdPreviewSurface.h"

namespace crayg {

UsdPreviewSurface::UsdPreviewSurface(const Color &diffuseColor) : Material(), diffuseColor(diffuseColor) {
}

UsdPreviewSurface::UsdPreviewSurface(const std::string &name) : Material(name) {
}

UsdPreviewSurface::UsdPreviewSurface(const std::string &name, const Color &diffuseColor)
    : Material(name), diffuseColor(diffuseColor) {
}

Color UsdPreviewSurface::evaluate(const SurfaceInteraction &surfaceInteraction, IntegratorContext &integratorContext) {
    const Color reflectivity = getReflectivity();

    if (reflectivity.isBlack()) {
        return diffuseColor;
    }

    const Ray reflectionRay = surfaceInteraction.spawnReflectionRayFromSurface();
    return diffuseColor + reflectivity * integratorContext.integrateRay(reflectionRay);
}

std::string UsdPreviewSurface::getType() {
    return "UsdPreviewSurface";
}

ShadingNodeOutputType UsdPreviewSurface::getOutputType() {
    return COLOR;
}

Color UsdPreviewSurface::getReflectivity() const {
    if (useSpecularWorkflow) {
        return specularColor;
    }
    return Color::createGrey(metallic);
}

}