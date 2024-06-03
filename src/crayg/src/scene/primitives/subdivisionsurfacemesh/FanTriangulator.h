#pragma once

#include "SubdivisionSurfaceMesh.h"

namespace crayg {

class FanTriangulator {
  public:
    explicit FanTriangulator(SubdivisionSurfaceMesh &subdivisionSurfaceMesh);
    FanTriangulator(std::vector<int> &faceVertexIndices, std::vector<int> &faceVertexCounts);
    void fanTriangulate(std::vector<TriangleMesh::FaceVertexIndices> &target);

  private:
    std::vector<int> &faceVertexIndices;
    std::vector<int> &faceVertexCounts;
};

} // crayg
