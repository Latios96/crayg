#include "UsdPreviewSurface.h"

namespace crayg {

UsdPreviewSurface::UsdPreviewSurface(const Color &diffuseColor) : diffuseColor(diffuseColor) {}

UsdPreviewSurface::UsdPreviewSurface(const std::string &name)
    : Material(name) {}

UsdPreviewSurface::UsdPreviewSurface(const std::string &name, const Color &diffuseColor)
    : Material(name), diffuseColor(diffuseColor) {}

Color UsdPreviewSurface::evaluate(const SurfaceInteraction &surfaceInteraction, IntegratorContext &integratorContext) {
    return diffuseColor;
}
std::string UsdPreviewSurface::getType() {
    return "UsdPreviewSurface";
}

}