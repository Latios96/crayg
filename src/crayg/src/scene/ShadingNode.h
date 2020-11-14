//
// Created by Jan on 14.11.2020.
//

#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_SHADINGNODE_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_SHADINGNODE_H_

#include <sceneIO/Serializable.h>
#include <basics/Color.h>

#include <utility>
#include <functional>

const bool INPUT_PLUG = true;
const bool OUTPUT_PLUG = false;

class ShadingNode;

template<typename T>
class Plug {
 public:
    Plug<T>(std::string name, ShadingNode *shadingNode, T defaultValue)
        : name(std::move(name)), shadingNode(shadingNode), defaultValue(defaultValue) {}

    std::string fullName();
    std::string name;
    ShadingNode *shadingNode;
    T defaultValue;
};

template<typename T>
class OutputPlug;

template<typename T>
class InputPlug : public Plug<T> {
 public:
    InputPlug(const std::string &name, ShadingNode *shadingNode, T defaultValue) :
        Plug<T>(name, shadingNode, defaultValue) {
    }

    T compute() {
        if (!input) {
            return Plug<T>::defaultValue;
        }
        return input->compute();
    }
    void connect(OutputPlug<T> *plug) {
        input = plug;
    }
    OutputPlug<T> *input = nullptr;
};

template<typename T>
class OutputPlug : public Plug<T> {
 public:
    OutputPlug(const std::string &name, ShadingNode *shadingNode, T defaultValue, std::function<T()> computor) :
        Plug<T>(name, shadingNode, defaultValue),
        computor(computor) {
    }
    T compute() {
        return computor();
    }
    void connect(InputPlug<T> *plug) {
        plug->input = this;
    }
    std::function<T()> computor;
};

class PlugPtr {
 public:
    PlugPtr() = default;;

    template<typename T>
    explicit PlugPtr(InputPlug<T> *plug) {
        ptr = plug;
    }
    template<typename T>
    explicit PlugPtr(OutputPlug<T> *plug) {
        ptr = plug;
    }
    void *getPtr() const {
        return ptr;
    }
 private:
    void *ptr = nullptr;
};

class ShadingNode : public Serializable {
 public:
    const std::string &getName() const;
    void setName(const std::string &name);
    void generateName();
    void serialize(Serializer &serializer) override;
    virtual void connectOutputToInput(const std::string &inputPlugName, PlugPtr outputPlug) = 0;
    virtual PlugPtr getPlugByName(const std::string &inputPlugName) = 0;
 private:
    std::string name;
};

template<typename T>
std::string Plug<T>::fullName() {
    return shadingNode->getName() + '.' + name;
}

#endif //CRAYG_SRC_CRAYG_SRC_SCENE_SHADINGNODE_H_
