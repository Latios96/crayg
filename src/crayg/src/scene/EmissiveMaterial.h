#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_EMISSIVEMATERIAL_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_EMISSIVEMATERIAL_H_

#include "Material.h"

namespace crayg {

class EmissiveMaterial : public Material {
 public:
    Color getDiffuseColor() override;
    float reflectivity() override;
    bool isEmissive() override;
    void connectOutputToInput(const std::string &inputPlugName, PlugPtr outputPlug) override;
    PlugPtr getPlugByName(const std::string &inputPlugName) override;
};

}

#endif //CRAYG_SRC_CRAYG_SRC_SCENE_EMISSIVEMATERIAL_H_
