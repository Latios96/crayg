#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_USDPREVIEWSURFACE_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_USDPREVIEWSURFACE_H_
#include "Material.h"

namespace crayg {

class UsdPreviewSurface : public Material {
  public:
    UsdPreviewSurface();
    explicit UsdPreviewSurface(const Color &diffuseColor);
    explicit UsdPreviewSurface(const std::string &name);
    UsdPreviewSurface(const std::string &name, const Color &diffuseColor);
    Color evaluate(const SurfaceInteraction &surfaceInteraction, IntegratorContext &integratorContext) override;
    std::string getType() override;
    ShadingNodeOutputType getOutputType() override;

    ColorShadingNodeInput diffuseColor = Color::createGrey(0.18f);
    ColorShadingNodeInput emissiveColor = Color::createBlack();
    bool useSpecularWorkflow = false;
    ColorShadingNodeInput specularColor = Color::createBlack();
    FloatShadingNodeInput metallic = 0;
    FloatShadingNodeInput roughness = 0.5f;
    FloatShadingNodeInput clearcoat = 0;
    FloatShadingNodeInput clearcoatRoughness = 0.01f;
    FloatShadingNodeInput opacity = 1;
    FloatShadingNodeInput opacityThreshold = 0;
    FloatShadingNodeInput ior = 1.5;
    Color getReflectivity(const SurfaceInteraction &surfaceInteraction);
};

} // namespace crayg
#endif // CRAYG_SRC_CRAYG_SRC_SCENE_USDPREVIEWSURFACE_H_
