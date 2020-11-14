//
// Created by Jan on 14.11.2020.
//

#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_SHADINGNODE_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_SHADINGNODE_H_

#include <sceneIO/Serializable.h>

class ShadingNode : public Serializable {
 public:
    const std::string &getName() const;
    void setName(const std::string &name);
    void generateName();
 private:
    std::string name;
};

#endif //CRAYG_SRC_CRAYG_SRC_SCENE_SHADINGNODE_H_
