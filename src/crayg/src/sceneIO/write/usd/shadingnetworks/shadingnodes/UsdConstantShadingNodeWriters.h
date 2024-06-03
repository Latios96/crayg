#pragma once

#include "scene/shadingnetworks/shadingnodes/ConstantShadingNodes.h"
#include "sceneIO/write/usd/base/BaseUsdShadingNodeWriter.h"

namespace crayg {

// todo refactor and replace with one templated version

class UsdFloatConstantWriter : public BaseUsdShadingNodeWriter<FloatConstant> {
  public:
    explicit UsdFloatConstantWriter(FloatConstant &craygObject, UsdShadingNodeWriteCache &usdShadingNodeWriteCache);
    pxr::UsdShadeShader write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) override;
    pxr::UsdShadeOutput getOutput(pxr::UsdShadeShader &usdShadeShader) override;

  protected:
    std::string getTranslatedType() override;
};

class UsdIntConstantWriter : public BaseUsdShadingNodeWriter<IntConstant> {
  public:
    explicit UsdIntConstantWriter(IntConstant &craygObject, UsdShadingNodeWriteCache &usdShadingNodeWriteCache);
    pxr::UsdShadeShader write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) override;
    pxr::UsdShadeOutput getOutput(pxr::UsdShadeShader &usdShadeShader) override;

  protected:
    std::string getTranslatedType() override;
};

class UsdVector2fConstantWriter : public BaseUsdShadingNodeWriter<Vector2fConstant> {
  public:
    explicit UsdVector2fConstantWriter(Vector2fConstant &craygObject,
                                       UsdShadingNodeWriteCache &usdShadingNodeWriteCache);
    pxr::UsdShadeShader write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) override;
    pxr::UsdShadeOutput getOutput(pxr::UsdShadeShader &usdShadeShader) override;

  protected:
    std::string getTranslatedType() override;
};

class UsdColorConstantWriter : public BaseUsdShadingNodeWriter<ColorConstant> {
  public:
    explicit UsdColorConstantWriter(ColorConstant &craygObject, UsdShadingNodeWriteCache &usdShadingNodeWriteCache);
    pxr::UsdShadeShader write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) override;
    pxr::UsdShadeOutput getOutput(pxr::UsdShadeShader &usdShadeShader) override;

  protected:
    std::string getTranslatedType() override;
};

} // crayg
