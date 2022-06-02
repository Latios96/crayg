//
// Created by Jan on 13.05.2022.
//

#ifndef CRAYG_SRC_CRAYGUSD_SRC_USDMESHTRANSLATOR_H_
#define CRAYG_SRC_CRAYGUSD_SRC_USDMESHTRANSLATOR_H_

#include "sceneIO/CraygUsdBase.h"
#include "BaseUsdImageableTranslator.h"
#include <pxr/usd/usdGeom/mesh.h>
#include "scene/TriangleMesh.h"

namespace crayg {

class UsdMeshTranslator : public BaseUsdImageableTranslator<pxr::UsdGeomMesh, TriangleMesh> {
 public:
    UsdMeshTranslator(const pxr::UsdGeomMesh &usdPrim, UsdMaterialTranslationCache &usdMaterialTranslationCache);
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
