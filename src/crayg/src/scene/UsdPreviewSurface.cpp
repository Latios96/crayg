#include "UsdPreviewSurface.h"

namespace crayg {

UsdPreviewSurface::UsdPreviewSurface(const Color &diffuseColor) : diffuseColor(diffuseColor) {}

UsdPreviewSurface::UsdPreviewSurface(const std::string &name, const Color &diffuseColor)
    : Material(name), diffuseColor(diffuseColor) {}
Color UsdPreviewSurface::getDiffuseColor() {
    return diffuseColor;
}
Color UsdPreviewSurface::evaluate(const SurfaceInteraction &surfaceInteraction) {
    return diffuseColor;
}
std::string UsdPreviewSurface::getType() {
    return "UsdPreviewSurface";
}

}