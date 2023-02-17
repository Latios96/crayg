#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_USDSUBDIVISIONSURFACEMESHREADER_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_USDSUBDIVISIONSURFACEMESHREADER_H_

#include "sceneIO/usd/CraygUsdBase.h"
#include "BaseUsdImageableReader.h"
#include <pxr/usd/usdGeom/mesh.h>
#include "scene/primitives/subdivisionsurfacemesh/SubdivisionSurfaceMesh.h"
#include <pxr/imaging/hd/meshUtil.h>

namespace crayg {

class UsdSubdivisionSurfaceMeshReader : public BaseUsdImageableReader<pxr::UsdGeomMesh, SubdivisionSurfaceMesh> {
 public:
    UsdSubdivisionSurfaceMeshReader(const pxr::UsdGeomMesh &usdPrim, UsdMaterialReadCache &usdMaterialTranslationCache);
    std::shared_ptr<SubdivisionSurfaceMesh> read() override;
 protected:
    std::string getTranslatedType() override;
    void translatePoints(std::shared_ptr<SubdivisionSurfaceMesh> &subdivisionSurfaceMesh) const;
    void translateIndices(std::shared_ptr<SubdivisionSurfaceMesh> &subdivisionSurfaceMesh) const;
    void ensureCatmullClarkScheme() const;
 private:
    bool normalsAreAuthored() const;
    void translateNormals(std::shared_ptr<SubdivisionSurfaceMesh> subdivisionSurfaceMesh);
    void translateBoundaryInterpolation(std::shared_ptr<SubdivisionSurfaceMesh> sharedPtr);
};

} // crayg

#endif //CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_USDSUBDIVISIONSURFACEMESHREADER_H_
