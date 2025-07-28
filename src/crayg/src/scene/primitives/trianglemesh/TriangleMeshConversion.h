#pragma once

#include "TriangleMesh.h"
#include "scene/primitives/GroundPlane.h"

namespace crayg {

class TriangleMeshConversion {
  public:
    static void toTriangleMesh(GroundPlane &groundPlane, TriangleMesh &triangleMesh);
};

}
