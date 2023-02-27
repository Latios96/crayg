#ifndef CRAYG_SRC_CRAYG_TESTS_FIXTURES_SUBDIVISIONSURFACEMESHFIXTURES_H_
#define CRAYG_SRC_CRAYG_TESTS_FIXTURES_SUBDIVISIONSURFACEMESHFIXTURES_H_

#include "scene/primitives/subdivisionsurfacemesh/SubdivisionSurfaceMesh.h"

namespace crayg {

class SubdivisionSurfaceMeshFixtures {
  public:
    static void createUnitPlane(SubdivisionSurfaceMesh &subdivisionSurfaceMesh);
    static void createTriangleUnitPlane(SubdivisionSurfaceMesh &subdivisionSurfaceMesh);
    static void createUnitCube(SubdivisionSurfaceMesh &subdivisionSurfaceMesh);
};

} // crayg

#endif // CRAYG_SRC_CRAYG_TESTS_FIXTURES_SUBDIVISIONSURFACEMESHFIXTURES_H_
