#include <iostream>
#define NOMINMAX
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usd/prim.h>
#include <pxr/usd/usd/primRange.h>
#include <pxr/usd/usdGeom/mesh.h>
#include <pxr/imaging/hd/meshUtil.h>
#include <pxr/imaging/hd/meshTopology.h>
#include <pxr/base/vt/array.h>
#include <scene/TriangleMesh.h>

int main(int argc, char *argv[]) {
    //auto stage = pxr::UsdStage::Open("M:\\modelLibrary\\_input_to_convert\\Kitchen_set\\Kitchen_set\\Kitchen_set.usd");
    auto stage = pxr::UsdStage::Open("C:\\workspace\\crayg\\example_scenes\\polyPlane.usda");
    for (pxr::UsdPrim prim: stage->TraverseAll()) {
        if (prim.IsA<pxr::UsdGeomMesh>()) {
            std::cout << "Mesh " << prim.GetPath().GetText() << std::endl;
            pxr::UsdGeomMesh mesh(prim);
            pxr::TfToken scheme;
            mesh.GetSubdivisionSchemeAttr().Get(&scheme);
            pxr::TfToken orientation;
            mesh.GetOrientationAttr().Get(&orientation);
            pxr::VtIntArray faceVertexCounts, faceVertexIndices, holeIndices;
            mesh.GetFaceVertexCountsAttr().Get(&faceVertexCounts);
            mesh.GetFaceVertexIndicesAttr().Get(&faceVertexIndices);
            mesh.GetHoleIndicesAttr().Get(&holeIndices);
            pxr::HdMeshTopology topology(scheme, orientation, faceVertexCounts, faceVertexIndices, holeIndices);
            pxr::HdMeshUtil meshUtil(&topology, mesh.GetPath());
            pxr::VtVec3iArray triangleIndices;
            pxr::VtIntArray primitiveParams;
            meshUtil.ComputeTriangleIndices(&triangleIndices, &primitiveParams);
            std::cout << "Mesh triangleIndices" << triangleIndices << std::endl;

            crayg::TriangleMesh triangleMesh;
            pxr::VtVec3fArray points;
            mesh.GetPointsAttr().Get(&points);
            triangleMesh.points.reserve(points.size());
            for (const auto &point: points) {
                triangleMesh.points.emplace_back(point[0], point[1], point[2]);
            }
            triangleMesh.faceIndexes.reserve(triangleIndices.size());
            for (const auto &faceIndex: triangleIndices) {
                triangleMesh.faceIndexes.push_back(faceIndex[0]);
                triangleMesh.faceIndexes.push_back(faceIndex[1]);
                triangleMesh.faceIndexes.push_back(faceIndex[2]);
            }
            pxr::GfMatrix4d matrix;
            bool resetsXformStack = false;
            mesh.GetLocalTransformation(&matrix, &resetsXformStack);
            std::cout << matrix << std::endl;
        }
    }
    return 0;
}

