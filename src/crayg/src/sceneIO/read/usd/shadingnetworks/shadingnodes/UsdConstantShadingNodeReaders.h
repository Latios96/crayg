#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_SHADINGNETWORKS_SHADINGNODES_USDCONSTANTSHADINGNODEWRITERS_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_SHADINGNETWORKS_SHADINGNODES_USDCONSTANTSHADINGNODEWRITERS_H_

#include "scene/shadingnetworks/shadingnodes/ConstantShadingNodes.h"
#include "sceneIO/read/usd/base/BaseUsdShadingNodeReader.h"

namespace crayg {

class UsdFloatConstantReader : public BaseUsdShadingNodeReader<FloatConstant> {
  public:
    UsdFloatConstantReader(const pxr::UsdShadeShader &usdPrim, UsdShadingNodeReadCache &usdShadingNodeReadCache);
    std::shared_ptr<FloatConstant> read() override;

  protected:
    std::string getTranslatedType() override;
};

class UsdIntConstantReader : public BaseUsdShadingNodeReader<IntConstant> {
  public:
    UsdIntConstantReader(const pxr::UsdShadeShader &usdPrim, UsdShadingNodeReadCache &usdShadingNodeReadCache);
    std::shared_ptr<IntConstant> read() override;

  protected:
    std::string getTranslatedType() override;
};

class UsdVector2fConstantReader : public BaseUsdShadingNodeReader<Vector2fConstant> {
  public:
    UsdVector2fConstantReader(const pxr::UsdShadeShader &usdPrim, UsdShadingNodeReadCache &usdShadingNodeReadCache);
    std::shared_ptr<Vector2fConstant> read() override;

  protected:
    std::string getTranslatedType() override;
};

class UsdColorConstantReader : public BaseUsdShadingNodeReader<ColorConstant> {
  public:
    UsdColorConstantReader(const pxr::UsdShadeShader &usdPrim, UsdShadingNodeReadCache &usdShadingNodeReadCache);
    std::shared_ptr<ColorConstant> read() override;

  protected:
    std::string getTranslatedType() override;
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_SHADINGNETWORKS_SHADINGNODES_USDCONSTANTSHADINGNODEWRITERS_H_
