//
// Created by Jan on 05.06.2022.
//

#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_TRIANGLEMESHCONVERSION_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_TRIANGLEMESHCONVERSION_H_

#include "GroundPlane.h"
#include "TriangleMesh.h"

namespace crayg {

class TriangleMeshConversion {
 public:
    static void toTriangleMesh(const GroundPlane &groundPlane, TriangleMesh &triangleMesh);
};

} // crayg

#endif //CRAYG_SRC_CRAYG_SRC_SCENE_TRIANGLEMESHCONVERSION_H_
