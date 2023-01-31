#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_PRIMITIVES_SUBDIVISIONSURFACEMESH_FANTRIANGULATOR_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_PRIMITIVES_SUBDIVISIONSURFACEMESH_FANTRIANGULATOR_H_

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

#endif //CRAYG_SRC_CRAYG_SRC_SCENE_PRIMITIVES_SUBDIVISIONSURFACEMESH_FANTRIANGULATOR_H_
