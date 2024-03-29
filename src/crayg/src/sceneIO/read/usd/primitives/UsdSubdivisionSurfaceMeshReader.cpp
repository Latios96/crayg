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

} // crayg