#include "UsdGroundPlaneWriter.h"
#include "scene/primitives/trianglemesh/TriangleMeshConversion.h"

namespace crayg {
UsdGroundPlaneWriter::UsdGroundPlaneWriter(GroundPlane &craygObject,
                                           UsdMaterialWriteCache &usdMaterialWriteCache) : BaseUsdSceneObjectWriter(
    craygObject,
    usdMaterialWriteCache) {}

pxr::UsdGeomMesh UsdGroundPlaneWriter::write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) {
    TriangleMesh triangleMesh;
    TriangleMeshConversion::toTriangleMesh(craygObject, triangleMesh);

    _SpecialUsdTriangleMeshWriter usdTriangleMeshWriter(triangleMesh, usdMaterialWriteCache);
    return usdTriangleMeshWriter.write(stage, usdPathFactory);
}
std::string UsdGroundPlaneWriter::getTranslatedType() {
    return BaseUsdSceneObjectWriter::getTranslatedType();
}

std::string _SpecialUsdTriangleMeshWriter::getTranslatedType() {
    return "GroundPlane";
}
_SpecialUsdTriangleMeshWriter::_SpecialUsdTriangleMeshWriter(TriangleMesh &craygObject,
                                                             UsdMaterialWriteCache &usdMaterialWriteCache)
    : UsdTriangleMeshWriter(craygObject, usdMaterialWriteCache) {}
} // crayg