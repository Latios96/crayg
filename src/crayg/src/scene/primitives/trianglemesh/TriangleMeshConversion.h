#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_TRIANGLEMESHCONVERSION_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_TRIANGLEMESHCONVERSION_H_

#include "scene/primitives/GroundPlane.h"
#include "TriangleMesh.h"

namespace crayg {

class TriangleMeshConversion {
 public:
    static void toTriangleMesh(const GroundPlane &groundPlane, TriangleMesh &triangleMesh);
};

} // crayg

#endif //CRAYG_SRC_CRAYG_SRC_SCENE_TRIANGLEMESHCONVERSION_H_
