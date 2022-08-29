#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_USDPREVIEWSURFACE_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_USDPREVIEWSURFACE_H_
#include "Material.h"
namespace crayg {

class UsdPreviewSurface : public Material {
 public:
    explicit UsdPreviewSurface(const Color &diffuseColor);
    explicit UsdPreviewSurface(const std::string &name);
    UsdPreviewSurface(const std::string &name, const Color &diffuseColor);
    Color evaluate(const SurfaceInteraction &surfaceInteraction, IntegratorContext &integratorContext) override;
    std::string getType() override;

    Color diffuseColor = Color::createGrey(0.18);
    Color emissiveColor = Color::createBlack();
    bool useSpecularWorkflow = false;
    Color specularColor = Color::createBlack();
    float metallic = 0;
    float roughness = 0.5f;
    float clearcoat = 0;
    float clearcoatRoughness = 0.01f;
    float opacity = 1;
    float opacityThreshold = 0;
    float ior = 1.5;
};

} // namespace crayg
#endif // CRAYG_SRC_CRAYG_SRC_SCENE_USDPREVIEWSURFACE_H_
