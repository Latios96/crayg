//
// Created by Jan on 05.06.2022.
//

#include "UsdGroundPlaneWriter.h"
#include "scene/TriangleMeshConversion.h"

namespace crayg {
UsdGroundPlaneWriter::UsdGroundPlaneWriter(const std::shared_ptr<GroundPlane> &craygObject) : BaseUsdSceneObjectWriter(
    craygObject) {}

pxr::UsdGeomMesh UsdGroundPlaneWriter::write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) {
    auto triangleMesh = std::make_shared<TriangleMesh>();
    TriangleMeshConversion::toTriangleMesh(*craygObject, *triangleMesh);

    _SpecialUsdTriangleMeshWriter usdTriangleMeshWriter(triangleMesh);
    return usdTriangleMeshWriter.write(stage, usdPathFactory);
}
std::string UsdGroundPlaneWriter::getTranslatedType() {
    return BaseUsdSceneObjectWriter::getTranslatedType();
}

_SpecialUsdTriangleMeshWriter::_SpecialUsdTriangleMeshWriter(const std::shared_ptr<TriangleMesh> &craygObject)
    : UsdTriangleMeshWriter(craygObject) {}
std::string _SpecialUsdTriangleMeshWriter::getTranslatedType() {
    return "GroundPlane";
}
} // crayg