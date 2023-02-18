#include "UsdGroundPlaneWriter.h"
#include "scene/primitives/trianglemesh/TriangleMeshConversion.h"

namespace crayg {

class _GroundPlaneUsdTriangleMeshWriter : public UsdTriangleMeshWriter {
 public:
    _GroundPlaneUsdTriangleMeshWriter(TriangleMesh &craygObject,
                                      UsdMaterialWriteCache &usdMaterialWriteCache) : UsdTriangleMeshWriter(craygObject,
                                                                                                            usdMaterialWriteCache) {}
 protected:
    std::string getTranslatedType() override {
        return "GroundPlane";
    }
};

UsdGroundPlaneWriter::UsdGroundPlaneWriter(GroundPlane &craygObject,
                                           UsdMaterialWriteCache &usdMaterialWriteCache) : BaseUsdSceneObjectWriter(
    craygObject,
    usdMaterialWriteCache) {}

pxr::UsdGeomMesh UsdGroundPlaneWriter::write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) {
    TriangleMesh triangleMesh;
    TriangleMeshConversion::toTriangleMesh(craygObject, triangleMesh);

    _GroundPlaneUsdTriangleMeshWriter usdTriangleMeshWriter(triangleMesh, usdMaterialWriteCache);
    return usdTriangleMeshWriter.write(stage, usdPathFactory);
}
std::string UsdGroundPlaneWriter::getTranslatedType() {
    return BaseUsdSceneObjectWriter::getTranslatedType();
}

} // crayg