#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_DIFFUSEMATERIAL_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_DIFFUSEMATERIAL_H_

#include "Material.h"

namespace crayg {

class DiffuseMaterial : public Material {
 public:
    DiffuseMaterial();
    explicit DiffuseMaterial(const Color &diffuseColor);
    DiffuseMaterial(const std::string &name, const Color &diffuseColor);
    Color getDiffuseColor() override;
    Color diffuseColor;
    void connectOutputToInput(const std::string &inputPlugName, PlugPtr outputPlug) override;
    PlugPtr getPlugByName(const std::string &inputPlugName) override;
    float reflectivity() override;
    bool isEmissive() override;
};

}

#endif //CRAYG_SRC_CRAYG_SRC_SCENE_DIFFUSEMATERIAL_H_
