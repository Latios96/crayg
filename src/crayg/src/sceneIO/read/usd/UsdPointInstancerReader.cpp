#include "UsdPointInstancerReader.h"
#include "UsdMeshReader.h"
#include "UsdSphereReader.h"
#include "UsdSubdivisionSurfaceMeshReader.h"
#include <pxr/usd/usd/primRange.h>
#include <pxr/usd/usdGeom/mesh.h>
#include <pxr/usd/usdGeom/sphere.h>

namespace crayg {

UsdPointInstancerReader::UsdPointInstancerReader(const pxr::UsdGeomPointInstancer &usdPrim,
                                                 UsdMaterialReadCache &usdMaterialTranslationCache)
    : BaseUsdImageableReader(usdPrim, usdMaterialTranslationCache) {
}

std::string UsdPointInstancerReader::getTranslatedType() {
    return "PointInstancer";
}

std::shared_ptr<PointInstancer> UsdPointInstancerReader::read() {
    auto pointInstancer = BaseUsdImageableReader::read();

    readIds(pointInstancer);
    readProtoIndices(pointInstancer);
    readTransforms(pointInstancer);
    readProtos(pointInstancer);

    return pointInstancer;
}

void UsdPointInstancerReader::readIds(std::shared_ptr<PointInstancer> &pointInstancer) const {
    pxr::VtInt64Array ids;
    usdPrim.GetIdsAttr().Get(&ids, timeCodeToRead);
    pointInstancer->ids.reserve(ids.size());
    for (auto id : ids) {
        pointInstancer->ids.push_back(id);
    }
}

void UsdPointInstancerReader::readProtoIndices(std::shared_ptr<PointInstancer> &pointInstancer) const {
    pxr::VtIntArray protoIndices;
    usdPrim.GetProtoIndicesAttr().Get(&protoIndices);
    pointInstancer->protoIndices.reserve(protoIndices.size());
    for (auto protoIndex : protoIndices) {
        pointInstancer->protoIndices.push_back(protoIndex);
    }
}

void UsdPointInstancerReader::readTransforms(std::shared_ptr<PointInstancer> &pointInstancer) {
    pxr::VtMatrix4dArray protoTransforms;
    usdPrim.ComputeInstanceTransformsAtTime(&protoTransforms, timeCodeToRead, timeCodeToRead);
    pointInstancer->transforms.reserve(protoTransforms.size());
    for (auto &transform : protoTransforms) {
        pointInstancer->transforms.emplace_back(UsdConversions::convert(transform));
    }
    if (pointInstancer->transforms.empty()) {
        pointInstancer->transforms.resize(pointInstancer->ids.size());
    }
}

void UsdPointInstancerReader::readProtos(std::shared_ptr<PointInstancer> &pointInstancer) const {
    pxr::SdfPathVector protoSdfPaths;
    usdPrim.GetPrototypesRel().GetTargets(&protoSdfPaths);
    pointInstancer->protos.reserve(protoSdfPaths.size());

    for (auto &protoSdfPath : protoSdfPaths) {
        auto protoPrim = usdPrim.GetPrim().GetStage()->GetPrimAtPath(protoSdfPath);
        auto proto = std::make_shared<PointInstancer::Prototype>();
        for (auto prim : pxr::UsdPrimRange(protoPrim)) {
            if (UsdReadUtils::isSubdivisionSurfaceMesh(prim) && UsdReadUtils::primIsVisible(prim)) {
                UsdSubdivisionSurfaceMeshReader usdSubdivisionSurfaceMeshReader(pxr::UsdGeomMesh(prim),
                                                                                usdMaterialTranslationCache);
                auto subdMesh = usdSubdivisionSurfaceMeshReader.read();
                proto->members.push_back(subdMesh);
            } else if (prim.IsA<pxr::UsdGeomMesh>() && UsdReadUtils::primIsVisible(prim)) {
                UsdMeshReader usdMeshReader(pxr::UsdGeomMesh(prim), usdMaterialTranslationCache);
                auto mesh = usdMeshReader.read();
                proto->members.push_back(mesh);
            } else if (prim.IsA<pxr::UsdGeomSphere>() && UsdReadUtils::primIsVisible(prim)) {
                UsdSphereReader usdSphereReader(pxr::UsdGeomSphere(prim), usdMaterialTranslationCache);
                auto sphere = usdSphereReader.read();
                proto->members.push_back(sphere);
            }
        }
        pointInstancer->protos.push_back(proto);
    }
}
} // crayg