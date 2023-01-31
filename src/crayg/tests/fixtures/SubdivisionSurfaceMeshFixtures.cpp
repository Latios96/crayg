#include "SubdivisionSurfaceMeshFixtures.h"

namespace crayg {

void SubdivisionSurfaceMeshFixtures::createUnitPlane(SubdivisionSurfaceMesh &subdivisionSurfaceMesh) {
    subdivisionSurfaceMesh.points.emplace_back(-0.5f,0.f,-0.5f);
    subdivisionSurfaceMesh.points.emplace_back(0.5f,0.f,-0.5f);
    subdivisionSurfaceMesh.points.emplace_back(0.5f,0.f,0.5f);
    subdivisionSurfaceMesh.points.emplace_back(-0.5f,0.f,0.5f);

    subdivisionSurfaceMesh.faceVertexIndices.push_back(0);
    subdivisionSurfaceMesh.faceVertexIndices.push_back(1);
    subdivisionSurfaceMesh.faceVertexIndices.push_back(2);
    subdivisionSurfaceMesh.faceVertexIndices.push_back(3);

    subdivisionSurfaceMesh.faceVertexCounts.push_back(4);
}

void SubdivisionSurfaceMeshFixtures::createTriangleUnitPlane(SubdivisionSurfaceMesh &subdivisionSurfaceMesh) {
    subdivisionSurfaceMesh.points.emplace_back(-0.5f,0.f,-0.5f);
    subdivisionSurfaceMesh.points.emplace_back(0.5f,0.f,-0.5f);
    subdivisionSurfaceMesh.points.emplace_back(0.5f,0.f,0.5f);
    subdivisionSurfaceMesh.points.emplace_back(-0.5f,0.f,0.5f);

    subdivisionSurfaceMesh.faceVertexIndices.push_back(0);
    subdivisionSurfaceMesh.faceVertexIndices.push_back(1);
    subdivisionSurfaceMesh.faceVertexIndices.push_back(2);
    subdivisionSurfaceMesh.faceVertexIndices.push_back(0);
    subdivisionSurfaceMesh.faceVertexIndices.push_back(2);
    subdivisionSurfaceMesh.faceVertexIndices.push_back(3);

    subdivisionSurfaceMesh.faceVertexCounts.push_back(3);
    subdivisionSurfaceMesh.faceVertexCounts.push_back(3);
}

void SubdivisionSurfaceMeshFixtures::createUnitCube(SubdivisionSurfaceMesh &subdivisionSurfaceMesh) {
    subdivisionSurfaceMesh.points.emplace_back(-0.5f, -0.5f, 0.5f);
    subdivisionSurfaceMesh.points.emplace_back(0.5f, -0.5f, 0.5f);
    subdivisionSurfaceMesh.points.emplace_back(-0.5f, 0.5f, 0.5f);
    subdivisionSurfaceMesh.points.emplace_back(0.5f, 0.5f, 0.5f);
    subdivisionSurfaceMesh.points.emplace_back(-0.5f, 0.5f, -0.5f);
    subdivisionSurfaceMesh.points.emplace_back(0.5f, 0.5f, -0.5f);
    subdivisionSurfaceMesh.points.emplace_back(-0.5f, -0.5f, -0.5f);
    subdivisionSurfaceMesh.points.emplace_back(0.5f, -0.5f, -0.5f);

    subdivisionSurfaceMesh.faceVertexIndices.insert(subdivisionSurfaceMesh.faceVertexIndices.end(), {0, 1, 3, 2,
                                                                                                     2, 3, 5, 4,
                                                                                                     4, 5, 7, 6,
                                                                                                     6, 7, 1, 0,
                                                                                                     1, 7, 5, 3,
                                                                                                     6, 0, 2, 4});

    subdivisionSurfaceMesh.faceVertexCounts.resize(6, 4);
}

} // crayg