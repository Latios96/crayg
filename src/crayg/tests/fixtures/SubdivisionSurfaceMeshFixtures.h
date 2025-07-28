#pragma once

#include "scene/primitives/subdivisionsurfacemesh/SubdivisionSurfaceMesh.h"

namespace crayg {

class SubdivisionSurfaceMeshFixtures {
  public:
    static void createUnitPlane(SubdivisionSurfaceMesh &subdivisionSurfaceMesh);
    static void createTriangleUnitPlane(SubdivisionSurfaceMesh &subdivisionSurfaceMesh);
    static void createUnitCube(SubdivisionSurfaceMesh &subdivisionSurfaceMesh);
};

}
