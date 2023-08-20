#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDPOINTINSTANCERWRITER_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDPOINTINSTANCERWRITER_H_
#include "scene/primitives/PointInstancer.h"
#include "sceneIO/write/usd/base/BaseUsdSceneObjectWriter.h"
#include <pxr/usd/usdGeom/pointInstancer.h>

namespace crayg {

class UsdPointInstancerWriter : public BaseUsdSceneObjectWriter<pxr::UsdGeomPointInstancer, PointInstancer> {
  public:
    UsdPointInstancerWriter(PointInstancer &craygObject, UsdMaterialWriteCache &usdMaterialWriteCache);
    pxr::UsdGeomPointInstancer write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) override;

  protected:
    std::string getTranslatedType() override;
    void writeIds(const pxr::UsdGeomPointInstancer &usdPointInstancer);
    void writeProtoIndices(const pxr::UsdGeomPointInstancer &usdPointInstancer);
    void writeTransforms(const pxr::UsdGeomPointInstancer &usdPointInstancer);
    void writeProtos(pxr::UsdStagePtr &stage, const pxr::UsdGeomPointInstancer &usdPointInstancer,
                     UsdPathFactory &usdPathFactory);
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDPOINTINSTANCERWRITER_H_
