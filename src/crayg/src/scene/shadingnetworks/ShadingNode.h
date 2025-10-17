#pragma once

#include "crayg/foundation/enums/EnumFormatter.h"
#include "crayg/foundation/exceptions/Exceptions.h"
#include <basics/Color.h>
#include <basics/Vector2.h>
#include <functional>
#include <integrators/SurfaceInteraction.h>
#include <ostream>
#include <utility>

namespace crayg {

class ShadingNode;

enum class ShadingNodeOutputType { INT, FLOAT, VECTOR2F, COLOR };

class ShadingNodeInput {
  public:
    void connectTo(const std::shared_ptr<ShadingNode> &newInput);

    virtual bool isCompatibleTo(ShadingNodeOutputType shadingNodeType) const = 0;
    virtual ShadingNodeOutputType getOutputType() const = 0;
    bool hasInputConnection() const;

    bool operator==(const ShadingNodeInput &rhs) const;
    bool operator!=(const ShadingNodeInput &rhs) const;

    std::shared_ptr<ShadingNode> inputNode;
    virtual ~ShadingNodeInput();
};

class FloatShadingNodeInput : public ShadingNodeInput {
  public:
    FloatShadingNodeInput() = default;
    FloatShadingNodeInput(float value);
    bool isCompatibleTo(ShadingNodeOutputType shadingNodeType) const override;
    ShadingNodeOutputType getOutputType() const override;
    float evaluate(const SurfaceInteraction &surfaceInteraction);
    float value;
    bool operator==(const FloatShadingNodeInput &rhs) const;
    bool operator!=(const FloatShadingNodeInput &rhs) const;
    friend std::ostream &operator<<(std::ostream &os, const FloatShadingNodeInput &input);
};

class IntShadingNodeInput : public ShadingNodeInput {
  public:
    IntShadingNodeInput() = default;
    IntShadingNodeInput(int value);
    bool isCompatibleTo(ShadingNodeOutputType shadingNodeType) const override;
    ShadingNodeOutputType getOutputType() const override;
    int evaluate(const SurfaceInteraction &surfaceInteraction);
    int value;
    bool operator==(const IntShadingNodeInput &rhs) const;
    bool operator!=(const IntShadingNodeInput &rhs) const;
    friend std::ostream &operator<<(std::ostream &os, const IntShadingNodeInput &input);
};

class Vector2fShadingNodeInput : public ShadingNodeInput {
  public:
    Vector2fShadingNodeInput() = default;
    Vector2fShadingNodeInput(const Vector2f &value);
    bool isCompatibleTo(ShadingNodeOutputType shadingNodeType) const override;
    ShadingNodeOutputType getOutputType() const override;
    Vector2f evaluate(const SurfaceInteraction &surfaceInteraction);
    Vector2f value;
    bool operator==(const Vector2fShadingNodeInput &rhs) const;
    bool operator!=(const Vector2fShadingNodeInput &rhs) const;
    friend std::ostream &operator<<(std::ostream &os, const Vector2fShadingNodeInput &input);
};

class ColorShadingNodeInput : public ShadingNodeInput {
  public:
    ColorShadingNodeInput() = default;
    ColorShadingNodeInput(const Color &value);

    bool isCompatibleTo(ShadingNodeOutputType shadingNodeType) const override;
    ShadingNodeOutputType getOutputType() const override;
    Color evaluate(const SurfaceInteraction &surfaceInteraction);
    Color value;
    bool operator==(const ColorShadingNodeInput &rhs) const;
    bool operator!=(const ColorShadingNodeInput &rhs) const;
    friend std::ostream &operator<<(std::ostream &os, const ColorShadingNodeInput &input);
};

class ShadingNode {
  public:
    ShadingNode();
    explicit ShadingNode(std::string name);
    std::string getName() const;
    void setName(const std::string &name);
    virtual std::string getType() const = 0;
    virtual ShadingNodeOutputType getOutputType() = 0;

    virtual float evaluateFloat(const SurfaceInteraction &surfaceInteraction) {
        CRAYG_LOG_AND_THROW_RUNTIME_ERROR("Can not evaluate to float on ShadingNode '{}' of type {}", getName(),
                                          getType());
    };

    virtual Vector2f evaluateVector2f(const SurfaceInteraction &surfaceInteraction) {
        CRAYG_LOG_AND_THROW_RUNTIME_ERROR("Can not evaluate to Vector2f on ShadingNode '{}' of type {}", getName(),
                                          getType());
    };

    virtual int evaluateInt(const SurfaceInteraction &surfaceInteraction) {
        CRAYG_LOG_AND_THROW_RUNTIME_ERROR("Can not evaluate to int on ShadingNode '{}' of type {}", getName(),
                                          getType());
    };

    virtual Color evaluateColor(const SurfaceInteraction &surfaceInteraction) {
        CRAYG_LOG_AND_THROW_RUNTIME_ERROR("Can not evaluate to Color on ShadingNode '{}' of type {}", getName(),
                                          getType());
    };

    virtual ~ShadingNode();

  private:
    std::string name;
};

}

CRAYG_FMT_ENUM_FORMATTER_H(crayg::ShadingNodeOutputType);
