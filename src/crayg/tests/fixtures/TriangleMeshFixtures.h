#ifndef CRAYG_SRC_CRAYG_TESTS_FIXTURES_TRIANGLEMESHFIXTURES_H_
#define CRAYG_SRC_CRAYG_TESTS_FIXTURES_TRIANGLEMESHFIXTURES_H_

#include "scene/trianglemesh/TriangleMesh.h"

namespace crayg {

class TriangleMeshFixtures {
 public:
/*
 (0,0,0)       (0,0,1)        (0,0,2)
 v0------------v1-------------v2
 |             |              |
 |             |              |
 v3------------v4-------------v5
 (1,0,0)       (1,0,1)        (1,0,2)

 Triangles:
 0: v0,v3,v1
 1: v1,v3,v4
 2: v1,v4,v2
 3: v2,v4,v5
 */
    static TriangleMesh createPrimVarFixtureMesh() {
        TriangleMesh triangleMesh;

        triangleMesh.points.emplace_back(0.0f, 0.0f, 0.0f);
        triangleMesh.points.emplace_back(0.0f, 0.0f, 1.0f);
        triangleMesh.points.emplace_back(0.0f, 0.0f, 2.0f);
        triangleMesh.points.emplace_back(1.0f, 0.0f, 0.0f);
        triangleMesh.points.emplace_back(1.0f, 0.0f, 1.0f);
        triangleMesh.points.emplace_back(1.0f, 0.0f, 2.0f);

        triangleMesh.faceVertexIndices.emplace_back(0, 3, 1);
        triangleMesh.faceVertexIndices.emplace_back(1, 3, 4);
        triangleMesh.faceVertexIndices.emplace_back(1, 4, 2);
        triangleMesh.faceVertexIndices.emplace_back(2, 4, 5);

        triangleMesh.init();
        return triangleMesh;
    }

    static TriangleMesh createSingleTriangle() {
        TriangleMesh triangleMesh;

        triangleMesh.points.emplace_back(0.0f, 0.0f, 0.0f);
        triangleMesh.points.emplace_back(0.0f, 1.0f, 0.0f);
        triangleMesh.points.emplace_back(1.0f, 0.0f, 0.0f);

        triangleMesh.faceVertexIndices.emplace_back(0, 1, 2);

        triangleMesh.init();
        return triangleMesh;
    }
};

}

#endif //CRAYG_SRC_CRAYG_TESTS_FIXTURES_TRIANGLEMESHFIXTURES_H_
