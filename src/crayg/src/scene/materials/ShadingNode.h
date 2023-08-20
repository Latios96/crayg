#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_SHADINGNODE_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_SHADINGNODE_H_

#include "utils/EnumUtils.h"
#include <basics/Color.h>
#include <basics/Vector2.h>
#include <functional>
#include <integrators/SurfaceInteraction.h>
#include <utility>

namespace crayg {

class ShadingNode;

enum ShadingNodeOutputType { INT, FLOAT, VECTOR2F, COLOR };

class ShadingNodeInput {
  public:
    void connectTo(const std::shared_ptr<ShadingNode> &newInput);

    virtual bool isCompatibleTo(ShadingNodeOutputType shadingNodeType) const = 0;
    virtual ShadingNodeOutputType getOutputType() const = 0;

    std::shared_ptr<ShadingNode> inputNode;
    virtual ~ShadingNodeInput();
};

class FloatShadingNodeInput : public ShadingNodeInput {
  public:
    bool isCompatibleTo(ShadingNodeOutputType shadingNodeType) const;
    ShadingNodeOutputType getOutputType() const override;
    float evaluate(const SurfaceInteraction &surfaceInteraction);
    float value;
};

class IntShadingNodeInput : public ShadingNodeInput {
  public:
    bool isCompatibleTo(ShadingNodeOutputType shadingNodeType) const;
    ShadingNodeOutputType getOutputType() const override;
    int evaluate(const SurfaceInteraction &surfaceInteraction);
    int value;
};

class Vector2fShadingNodeInput : public ShadingNodeInput {
  public:
    bool isCompatibleTo(ShadingNodeOutputType shadingNodeType) const;
    ShadingNodeOutputType getOutputType() const override;
    Vector2f evaluate(const SurfaceInteraction &surfaceInteraction);
    Vector2f value;
};

class ColorShadingNodeInput : public ShadingNodeInput {
  public:
    bool isCompatibleTo(ShadingNodeOutputType shadingNodeType) const;
    ShadingNodeOutputType getOutputType() const override;
    Color evaluate(const SurfaceInteraction &surfaceInteraction);
    Color value;
};

class ShadingNode {
  public:
    ShadingNode();
    explicit ShadingNode(std::string name);
    std::string getName() const;
    virtual std::string getType() = 0;
    virtual ShadingNodeOutputType getOutputType() = 0;

    virtual float evaluateFloat(const SurfaceInteraction &surfaceInteraction) {
        throw std::runtime_error(
            fmt::format("Can not evaluate to float on ShadingNode '{}' of type {}", getName(), getType()));
    };

    virtual Vector2f evaluateVector2f(const SurfaceInteraction &surfaceInteraction) {
        throw std::runtime_error(
            fmt::format("Can not evaluate to Vector2f on ShadingNode '{}' of type {}", getName(), getType()));
    };

    virtual int evaluateInt(const SurfaceInteraction &surfaceInteraction) {
        throw std::runtime_error(
            fmt::format("Can not evaluate to int on ShadingNode '{}' of type {}", getName(), getType()));
    };

    virtual Color evaluateColor(const SurfaceInteraction &surfaceInteraction) {
        throw std::runtime_error(
            fmt::format("Can not evaluate to Color on ShadingNode '{}' of type {}", getName(), getType()));
    };

    virtual ~ShadingNode();

  private:
    std::string name;
};

}

CRAYG_FMT_ENUM_FORMATTER(crayg::ShadingNodeOutputType);

#endif // CRAYG_SRC_CRAYG_SRC_SCENE_SHADINGNODE_H_
