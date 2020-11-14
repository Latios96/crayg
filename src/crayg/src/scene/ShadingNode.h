//
// Created by Jan on 14.11.2020.
//

#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_SHADINGNODE_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_SHADINGNODE_H_

#include <sceneIO/Serializable.h>
#include <basics/Color.h>

#include <utility>

const bool INPUT_PLUG = true;
const bool OUTPUT_PLUG = false;

class ShadingNode;

template<typename T, bool isInput>
class Plug {
 public:
    Plug(std::string name,
         ShadingNode *shadingNode,
         T defaultValue,
         Plug<T, !isInput> *input)
        : name(std::move(name)),
          shadingNode(shadingNode),
          defaultValue(defaultValue),
          input(input) {}
    Plug(std::string name, ShadingNode *shadingNode, T defaultValue)
        : name(std::move(name)), shadingNode(shadingNode), defaultValue(defaultValue) {}
    T compute() {
        if (!input) {
            return defaultValue;
        }
        return computor();
    }
    void connect(Plug<T, !isInput> *plug) {
        input = plug;
    }

    void connectTo(Plug<T, !isInput> *plug) {
        plug->input = this;
    }
    std::string fullName() {
        return shadingNode->getName() + name;
    }
    std::string name;
    ShadingNode *shadingNode;
    T defaultValue;
    Plug<T, !isInput> *input = nullptr;
};

class ShadingNode : public Serializable {
 public:
    const std::string &getName() const;
    void setName(const std::string &name);
    void generateName();
    void serialize(Serializer &serializer) override;
 private:
    std::string name;
};

#endif //CRAYG_SRC_CRAYG_SRC_SCENE_SHADINGNODE_H_
