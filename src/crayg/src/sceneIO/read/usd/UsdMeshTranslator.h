//
// Created by Jan on 13.05.2022.
//

#ifndef CRAYG_SRC_CRAYGUSD_SRC_USDMESHTRANSLATOR_H_
#define CRAYG_SRC_CRAYGUSD_SRC_USDMESHTRANSLATOR_H_

#include "CraygUsdBase.h"
#include "BaseUsdXformableTranslator.h"
#include <pxr/usd/usdGeom/mesh.h>
#include "scene/TriangleMesh.h"

namespace crayg {

class UsdMeshTranslator : public BaseUsdXformableTranslator<pxr::UsdGeomMesh, TriangleMesh> {
 public:
    explicit UsdMeshTranslator(const pxr::UsdGeomMesh &usdGeomMesh);
    std::shared_ptr<TriangleMesh> translate() override;
 protected:
    std::string getTranslatedType() override;
 private:
    void computeTriangleIndices(pxr::VtVec3iArray &triangleIndices) const;
    void translatePoints(std::shared_ptr<TriangleMesh> &triangleMesh) const;
    void translateFaceIndices(std::shared_ptr<TriangleMesh> &triangleMesh, pxr::VtVec3iArray &triangleIndices) const;
};

}

#endif //CRAYG_SRC_CRAYGUSD_SRC_USDMESHTRANSLATOR_H_
