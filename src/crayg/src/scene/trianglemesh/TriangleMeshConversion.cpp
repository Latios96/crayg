//
// Created by Jan on 05.06.2022.
//

#include "TriangleMeshConversion.h"

namespace crayg {
void TriangleMeshConversion::toTriangleMesh(const GroundPlane &groundPlane, TriangleMesh &triangleMesh) {
    triangleMesh.points.emplace_back(-1000.0f, 0.0f, -1000.0f);
    triangleMesh.points.emplace_back(-1000.0f, 0.0f, 1000.0f);
    triangleMesh.points.emplace_back(1000.0f, 0.0f, 1000.0f);
    triangleMesh.points.emplace_back(1000.0f, 0.0f, -1000.0f);

    triangleMesh.faceVertexIndices.push_back({0, 1, 2});
    triangleMesh.faceVertexIndices.push_back({2, 3, 0});

    triangleMesh.setMaterial(groundPlane.getMaterial());
    triangleMesh.setTransform(groundPlane.getTransform());
    triangleMesh.init();
}
} // crayg