//
// Created by Jan on 17.11.2020.
//

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
    void serialize(Serializer &serializer) override;
    void deserialize(Deserializer &deserializer) override;
    bool isEmissive() override;
};

}

#endif //CRAYG_SRC_CRAYG_SRC_SCENE_REFLECTIVEMATERIAL_H_
