//
// Created by Jan on 13.05.2022.
//

#ifndef CRAYG_SRC_CRAYGUSD_SRC_USDMESHTRANSLATOR_H_
#define CRAYG_SRC_CRAYGUSD_SRC_USDMESHTRANSLATOR_H_

#include "sceneIO/CraygUsdBase.h"
#include "BaseUsdImageableReader.h"
#include <pxr/usd/usdGeom/mesh.h>
#include "scene/TriangleMesh.h"

namespace crayg {

class UsdMeshReader : public BaseUsdImageableReader<pxr::UsdGeomMesh, TriangleMesh> {
 public:
    UsdMeshReader(const pxr::UsdGeomMesh &usdPrim, UsdMaterialReadCache &usdMaterialTranslationCache);
    std::shared_ptr<TriangleMesh> read() override;
 protected:
    std::string getTranslatedType() override;
 private:
    void computeTriangleIndices(pxr::VtVec3iArray &triangleIndices) const;
    void translatePoints(std::shared_ptr<TriangleMesh> &triangleMesh) const;
    void translateFaceIndices(std::shared_ptr<TriangleMesh> &triangleMesh, pxr::VtVec3iArray &triangleIndices) const;
};

}

#endif //CRAYG_SRC_CRAYGUSD_SRC_USDMESHTRANSLATOR_H_
