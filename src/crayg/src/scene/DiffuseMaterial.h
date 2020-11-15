//
// Created by Jan on 15.11.2020.
//

#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_DIFFUSEMATERIAL_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_DIFFUSEMATERIAL_H_

#include "Material.h"
class DiffuseMaterial : public Material {
 public:
    DiffuseMaterial();
    explicit DiffuseMaterial(const Color &diffuseColor);
    DiffuseMaterial(const std::string &name, const Color &diffuseColor);
    Color getDiffuseColor() override;
    void serialize(Serializer &serializer) override;
    void deserialize(Deserializer &deserializer) override;
    Color diffuseColor;
    void connectOutputToInput(const std::string &inputPlugName, PlugPtr outputPlug) override;
    PlugPtr getPlugByName(const std::string &inputPlugName) override;
};

#endif //CRAYG_SRC_CRAYG_SRC_SCENE_DIFFUSEMATERIAL_H_
