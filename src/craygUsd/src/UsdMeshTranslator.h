//
// Created by Jan on 13.05.2022.
//

#ifndef CRAYG_SRC_CRAYGUSD_SRC_USDMESHTRANSLATOR_H_
#define CRAYG_SRC_CRAYGUSD_SRC_USDMESHTRANSLATOR_H_

#include "CraygUsdBase.h"
#include <pxr/usd/usdGeom/mesh.h>
#include <scene/TriangleMesh.h>

namespace crayg {

class UsdMeshTranslator {
 public:
    explicit UsdMeshTranslator(const pxr::UsdGeomMesh &usdGeomMesh);
    std::shared_ptr<TriangleMesh> translate();
 private:
    pxr::UsdGeomMesh usdGeomMesh;
    void computeTriangleIndices(pxr::VtVec3iArray &triangleIndices) const;
    void translatePoints(std::shared_ptr<TriangleMesh> &triangleMesh) const;
    void translateFaceIndices(std::shared_ptr<TriangleMesh> &triangleMesh, pxr::VtVec3iArray &triangleIndices) const;
    void translateTransform(std::shared_ptr<TriangleMesh> &triangleMesh) const;
};

}

#endif //CRAYG_SRC_CRAYGUSD_SRC_USDMESHTRANSLATOR_H_
