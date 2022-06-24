#include "UsdGroundPlaneWriter.h"
#include "scene/trianglemesh/TriangleMeshConversion.h"

namespace crayg {
UsdGroundPlaneWriter::UsdGroundPlaneWriter(const std::shared_ptr<GroundPlane> &craygObject,
                                           UsdMaterialWriteCache &usdMaterialWriteCache) : BaseUsdSceneObjectWriter(
    craygObject,
    usdMaterialWriteCache) {}

pxr::UsdGeomMesh UsdGroundPlaneWriter::write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) {
    auto triangleMesh = std::make_shared<TriangleMesh>();
    TriangleMeshConversion::toTriangleMesh(*craygObject, *triangleMesh);

    _SpecialUsdTriangleMeshWriter usdTriangleMeshWriter(triangleMesh, usdMaterialWriteCache);
    return usdTriangleMeshWriter.write(stage, usdPathFactory);
}
std::string UsdGroundPlaneWriter::getTranslatedType() {
    return BaseUsdSceneObjectWriter::getTranslatedType();
}

std::string _SpecialUsdTriangleMeshWriter::getTranslatedType() {
    return "GroundPlane";
}
_SpecialUsdTriangleMeshWriter::_SpecialUsdTriangleMeshWriter(const std::shared_ptr<TriangleMesh> &craygObject,
                                                             UsdMaterialWriteCache &usdMaterialWriteCache)
    : UsdTriangleMeshWriter(craygObject, usdMaterialWriteCache) {}
} // crayg