#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_REFLECTIVEMATERIAL_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_REFLECTIVEMATERIAL_H_

#include "Material.h"

namespace crayg {

class ReflectiveMaterial : public Material {
 public:
    Color getDiffuseColor() override;
    float reflectivity() override;
    void connectOutputToInput(const std::string &inputPlugName, PlugPtr outputPlug) override;
    PlugPtr getPlugByName(const std::string &inputPlugName) override;
    bool isEmissive() override;
};

}

#endif //CRAYG_SRC_CRAYG_SRC_SCENE_REFLECTIVEMATERIAL_H_
