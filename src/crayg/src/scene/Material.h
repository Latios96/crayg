//
// Created by Jan on 14.11.2020.
//

#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_MATERIAL_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_MATERIAL_H_

#include <basics/Color.h>
#include <sceneIO/Serializable.h>
#include "ShadingNode.h"

namespace crayg {

class Material : public ShadingNode {
 public:
    explicit Material();
    explicit Material(const std::string &name);
    virtual Color getDiffuseColor() = 0;
    virtual float reflectivity() = 0;
    virtual bool isEmissive() = 0;
};

}

#endif //CRAYG_SRC_CRAYG_SRC_SCENE_MATERIAL_H_
