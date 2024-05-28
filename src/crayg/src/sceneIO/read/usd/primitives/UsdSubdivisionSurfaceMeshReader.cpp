#include "UsdSubdivisionSurfaceMeshReader.h"
#include "utils/Exceptions.h"

namespace crayg {

std::string UsdSubdivisionSurfaceMeshReader::getTranslatedType() {
    return "SubD mesh";
}

UsdSubdivisionSurfaceMeshReader::UsdSubdivisionSurfaceMeshReader(const pxr::UsdGeomMesh &usdPrim,
                                                                 UsdMaterialReadCache &usdMaterialTranslationCache)
    : BaseUsdImageableReader(usdPrim, usdMaterialTranslationCache) {
}

std::shared_ptr<SubdivisionSurfaceMesh> UsdSubdivisionSurfaceMeshReader::read() {
    ensureCatmullClarkScheme();

    auto subdivisionSurfaceMesh = BaseUsdImageableReader<pxr::UsdGeomMesh, SubdivisionSurfaceMesh>::read();

    translatePoints(subdivisionSurfaceMesh);
    translateIndices(subdivisionSurfaceMesh);
    translateBoundaryInterpolation(subdivisionSurfaceMesh);
    translateUvs(subdivisionSurfaceMesh);

    return subdivisionSurfaceMesh;
}

void UsdSubdivisionSurfaceMeshReader::ensureCatmullClarkScheme() const {
    auto subdivisionScheme =
        UsdUtils::getAttributeValueAs<pxr::TfToken>(usdPrim.GetSubdivisionSchemeAttr(), timeCodeToRead);
    if (subdivisionScheme != pxr::UsdGeomTokens->catmullClark) {
        CRAYG_LOG_AND_THROW(
            std::runtime_error(fmt::format("Can not read mesh with subdivision scheme {}", subdivisionScheme)));
    }
}

void UsdSubdivisionSurfaceMeshReader::translatePoints(
    std::shared_ptr<SubdivisionSurfaceMesh> &subdivisionSurfaceMesh) const {
    pxr::VtVec3fArray points;
    usdPrim.GetPointsAttr().Get(&points, timeCodeToRead);
    subdivisionSurfaceMesh->points.reserve(points.size());
    for (const auto &point : points) {
        subdivisionSurfaceMesh->points.emplace_back(point[0], point[1], -point[2]);
    }
}

void UsdSubdivisionSurfaceMeshReader::translateIndices(
    std::shared_ptr<SubdivisionSurfaceMesh> &subdivisionSurfaceMesh) const {
    pxr::VtIntArray faceVertexCounts;
    usdPrim.GetFaceVertexCountsAttr().Get(&faceVertexCounts, timeCodeToRead);
    subdivisionSurfaceMesh->faceVertexCounts.reserve(faceVertexCounts.size());

    pxr::VtIntArray faceVertexIndices;
    usdPrim.GetFaceVertexIndicesAttr().Get(&faceVertexIndices, timeCodeToRead);
    subdivisionSurfaceMesh->faceVertexIndices.reserve(faceVertexIndices.size());

    int offset = 0;
    for (auto faceVertexCount : faceVertexCounts) {
        subdivisionSurfaceMesh->faceVertexCounts.push_back(faceVertexCount);
        for (int i = faceVertexCount - 1; i >= 0; i--) {
            subdivisionSurfaceMesh->faceVertexIndices.push_back(faceVertexIndices[offset + i]);
        }
        offset += faceVertexCount;
    }
}

void UsdSubdivisionSurfaceMeshReader::translateBoundaryInterpolation(
    std::shared_ptr<SubdivisionSurfaceMesh> subdivisionSurfaceMesh) {
    auto interpolateBoundary =
        UsdUtils::getAttributeValueAs<pxr::TfToken>(usdPrim.GetInterpolateBoundaryAttr(), timeCodeToRead);
    if (interpolateBoundary == pxr::UsdGeomTokens->edgeAndCorner) {
        subdivisionSurfaceMesh->boundaryInterpolation = SubdivisionSurfaceMesh::BoundaryInterpolation::EDGE_AND_CORNER;
        return;
    }
    subdivisionSurfaceMesh->boundaryInterpolation = SubdivisionSurfaceMesh::BoundaryInterpolation::EDGE_ONLY;
}

void UsdSubdivisionSurfaceMeshReader::translateUvs(
    std::shared_ptr<SubdivisionSurfaceMesh> &subdivisionSurfaceMesh) const {
    std::optional<pxr::UsdGeomPrimvar> uvsPrimVar = UsdReadUtils::getAuthoredUvPrimVar(this->usdPrim);
    if (!uvsPrimVar) {
        return;
    }

    const pxr::TfToken uvsInterpolation = uvsPrimVar->GetInterpolation();

    if (uvsInterpolation != pxr::UsdGeomTokens->faceVarying) {
        Logger::warning(R"(UV interpolation "{}" of mesh {} is not supported)", uvsInterpolation, usdPrim.GetPath());
        return;
    }

    pxr::VtVec2fArray uvs;
    uvsPrimVar->Get(&uvs, timeCodeToRead);
    subdivisionSurfaceMesh->uvs.reserve(uvs.size());
    for (auto &uv : uvs) {
        Vector2f vec2f = UsdConversions::convert(uv);
        vec2f.y = 1 - vec2f.y;
        subdivisionSurfaceMesh->uvs.push_back(vec2f);
    }

    pxr::VtIntArray indices;
    uvsPrimVar->GetIndices(&indices);
    subdivisionSurfaceMesh->uvIndices.reserve(indices.size());
    for (auto &i : indices) {
        subdivisionSurfaceMesh->uvIndices.push_back(i);
    }
}

} // crayg