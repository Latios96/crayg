#include "FanTriangulator.h"

namespace crayg {

FanTriangulator::FanTriangulator(std::vector<int> &faceVertexIndices, std::vector<int> &faceVertexCounts)
    : faceVertexIndices(faceVertexIndices), faceVertexCounts(faceVertexCounts) {}

FanTriangulator::FanTriangulator(SubdivisionSurfaceMesh &subdivisionSurfaceMesh) : faceVertexIndices(
    subdivisionSurfaceMesh.faceVertexIndices), faceVertexCounts(subdivisionSurfaceMesh.faceVertexCounts) {}

void FanTriangulator::fanTriangulate(std::vector<TriangleMesh::FaceVertexIndices> &target) {
    int offset = 0;
    for (int faceVertexCount: faceVertexCounts) {
        for (int generatedTriangle = 0; generatedTriangle < (faceVertexCount - 2); generatedTriangle++) {
            target.emplace_back(faceVertexIndices[
                                    offset],
                                faceVertexIndices[
                                    offset + generatedTriangle + 1],
                                faceVertexIndices[
                                    offset + generatedTriangle + 2]);
        }
        offset+=faceVertexCount;
    }
}

} // crayg