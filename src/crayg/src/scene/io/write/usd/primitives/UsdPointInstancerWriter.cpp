#include "UsdPointInstancerWriter.h"
#include "UsdGroundPlaneWriter.h"
#include "UsdSphereWriter.h"
#include "UsdSubdivisionSurfaceMeshWriter.h"
#include "UsdTriangleMeshWriter.h"
#include "scene/primitives/GroundPlane.h"
#include "scene/primitives/Sphere.h"
#include "scene/primitives/subdivisionsurfacemesh/SubdivisionSurfaceMesh.h"
#include "scene/primitives/trianglemesh/TriangleMesh.h"
#include <pxr/base/gf/transform.h>

namespace crayg {

UsdPointInstancerWriter::UsdPointInstancerWriter(PointInstancer &craygObject,
                                                 UsdMaterialWriteCache &usdMaterialWriteCache)
    : BaseUsdSceneObjectWriter(craygObject, usdMaterialWriteCache) {
}

pxr::UsdGeomPointInstancer UsdPointInstancerWriter::write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) {
    auto usdPointInstancer = BaseUsdSceneObjectWriter::write(stage, usdPathFactory);

    writeIds(usdPointInstancer);
    writeProtoIndices(usdPointInstancer);
    writeTransforms(usdPointInstancer);
    writeProtos(stage, usdPointInstancer, usdPathFactory);

    return usdPointInstancer;
}

void UsdPointInstancerWriter::writeIds(const pxr::UsdGeomPointInstancer &usdPointInstancer) {
    pxr::VtInt64Array ids;
    ids.reserve(craygObject.ids.size());
    for (auto id : craygObject.ids) {
        ids.push_back(id);
    }
    usdPointInstancer.GetIdsAttr().Set(ids);
}

void UsdPointInstancerWriter::writeProtoIndices(const pxr::UsdGeomPointInstancer &usdPointInstancer) {
    pxr::VtIntArray protoIndices;
    protoIndices.reserve(craygObject.protoIndices.size());
    for (auto id : craygObject.protoIndices) {
        protoIndices.push_back(id);
    }
    usdPointInstancer.GetProtoIndicesAttr().Set(protoIndices);
}

void UsdPointInstancerWriter::writeTransforms(const pxr::UsdGeomPointInstancer &usdPointInstancer) {
    pxr::VtVec3fArray positions;
    positions.reserve(craygObject.ids.size());
    pxr::VtQuathArray orientations;
    orientations.reserve(craygObject.ids.size());
    pxr::VtVec3fArray scales;
    scales.reserve(craygObject.ids.size());

    for (auto &transform : craygObject.transforms) {
        auto matrix = UsdConversions::convert(transform.matrix);
        pxr::GfTransform usdTransform(matrix);
        positions.push_back(pxr::GfVec3f(usdTransform.GetTranslation()));
        orientations.push_back(pxr::GfQuath(usdTransform.GetRotation().GetQuat()));
        scales.push_back(pxr::GfVec3f(usdTransform.GetScale()));
    }

    usdPointInstancer.GetPositionsAttr().Set(positions);
    usdPointInstancer.GetOrientationsAttr().Set(orientations);
    usdPointInstancer.GetScalesAttr().Set(scales);
}

void UsdPointInstancerWriter::writeProtos(pxr::UsdStagePtr &stage, const pxr::UsdGeomPointInstancer &usdPointInstancer,
                                          UsdPathFactory &usdPathFactory) {
    for (auto &proto : craygObject.protos) {
        usdPointInstancer.GetPrototypesRel().AddTarget(pxr::SdfPath(proto->name));
        for (auto &member : proto->members) {
            if (member->getType() == "Sphere") {
                UsdSphereWriter(*std::static_pointer_cast<Sphere>(member), usdMaterialWriteCache)
                    .write(stage, usdPathFactory);
            } else if (member->getType() == "TriangleMesh") {
                UsdTriangleMeshWriter(*std::static_pointer_cast<TriangleMesh>(member), usdMaterialWriteCache)
                    .write(stage, usdPathFactory);
            } else if (member->getType() == "GroundPlane") {
                UsdGroundPlaneWriter(*std::static_pointer_cast<GroundPlane>(member), usdMaterialWriteCache)
                    .write(stage, usdPathFactory);
            } else if (member->getType() == "SubdivisionSurfaceMesh") {
                UsdSubdivisionSurfaceMeshWriter(*std::static_pointer_cast<SubdivisionSurfaceMesh>(member),
                                                usdMaterialWriteCache)
                    .write(stage, usdPathFactory);
            }
        }
    }
}

std::string UsdPointInstancerWriter::getTranslatedType() {
    return "PointInstancer";
}

}