#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_USDPREVIEWSURFACE_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_USDPREVIEWSURFACE_H_
#include "Material.h"
namespace crayg {
class UsdPreviewSurface : public Material {
 public:
    explicit UsdPreviewSurface(const Color &diffuseColor);
    UsdPreviewSurface(const std::string &name, const Color &diffuseColor);
    Color getDiffuseColor() override;
    Color evaluate(const SurfaceInteraction &surfaceInteraction) override;
    std::string getType() override;
 private:
    Color diffuseColor;
};
} // namespace crayg
#endif // CRAYG_SRC_CRAYG_SRC_SCENE_USDPREVIEWSURFACE_H_
