#include "UsdSubdivisionSurfaceMeshReader.h"

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
    translateFaceVertexCounts(subdivisionSurfaceMesh);

    return subdivisionSurfaceMesh;
}

void UsdSubdivisionSurfaceMeshReader::ensureCatmullClarkScheme() const {
    auto subdivisionScheme =
        UsdUtils::getAttributeValueAs<pxr::TfToken>(usdPrim.GetSubdivisionSchemeAttr(), timeCodeToRead);
    if (subdivisionScheme != pxr::UsdGeomTokens->catmullClark) {
        throw std::runtime_error(fmt::format("Can not read mesh with subdivision scheme {}", subdivisionScheme));
    }
}

void UsdSubdivisionSurfaceMeshReader::translatePoints(std::shared_ptr<SubdivisionSurfaceMesh> &subdivisionSurfaceMesh) const {
    pxr::VtVec3fArray points;
    usdPrim.GetPointsAttr().Get(&points, timeCodeToRead);
    subdivisionSurfaceMesh->points.reserve(points.size());
    for (const auto &point: points) {
        subdivisionSurfaceMesh->points.emplace_back(point[0], point[1], -point[2]);
    }
}

void UsdSubdivisionSurfaceMeshReader::translateIndices(std::shared_ptr<SubdivisionSurfaceMesh> &subdivisionSurfaceMesh) const {
    pxr::VtIntArray faceVertexIndices;
    usdPrim.GetFaceVertexIndicesAttr().Get(&faceVertexIndices, timeCodeToRead);
    subdivisionSurfaceMesh->faceVertexIndices.reserve(faceVertexIndices.size());
    for (auto i: faceVertexIndices) {
        subdivisionSurfaceMesh->faceVertexIndices.push_back(i);
    }
}

void UsdSubdivisionSurfaceMeshReader::translateFaceVertexCounts(std::shared_ptr<SubdivisionSurfaceMesh> &subdivisionSurfaceMesh) const {
    pxr::VtIntArray faceVertexCounts;
    usdPrim.GetFaceVertexCountsAttr().Get(&faceVertexCounts, timeCodeToRead);
    subdivisionSurfaceMesh->faceVertexCounts.reserve(faceVertexCounts.size());
    for (auto i: faceVertexCounts) {
        subdivisionSurfaceMesh->faceVertexCounts.push_back(i);
    }
}
} // crayg