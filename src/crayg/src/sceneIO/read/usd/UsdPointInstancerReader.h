#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_USDPOINTINSTANCERREADER_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_USDPOINTINSTANCERREADER_H_

#include "BaseUsdImageableReader.h"
#include "scene/primitives/PointInstancer.h"
#include "sceneIO/usd/CraygUsdBase.h"
#include <pxr/usd/usdGeom/pointInstancer.h>

namespace crayg {

class UsdPointInstancerReader : public BaseUsdImageableReader<pxr::UsdGeomPointInstancer, PointInstancer> {
  public:
    UsdPointInstancerReader(const pxr::UsdGeomPointInstancer &usdPrim,
                            UsdMaterialReadCache &usdMaterialTranslationCache);
    std::shared_ptr<PointInstancer> read() override;

  protected:
    std::string getTranslatedType() override;
    void readIds(std::shared_ptr<PointInstancer> &pointInstancer) const;
    void readProtoIndices(std::shared_ptr<PointInstancer> &pointInstancer) const;
    void readTransforms(std::shared_ptr<PointInstancer> &pointInstancer);
    void readProtos(std::shared_ptr<PointInstancer> &pointInstancer) const;
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_USDPOINTINSTANCERREADER_H_
