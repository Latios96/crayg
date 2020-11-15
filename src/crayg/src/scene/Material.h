//
// Created by Jan on 14.11.2020.
//

#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_MATERIAL_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_MATERIAL_H_

#include <basics/Color.h>
#include <sceneIO/Serializable.h>
#include "ShadingNode.h"

class Material : public ShadingNode {
 public:
    virtual Color getDiffuseColor() = 0;
};

#endif //CRAYG_SRC_CRAYG_SRC_SCENE_MATERIAL_H_
