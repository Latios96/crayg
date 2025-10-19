#pragma once

#include "crayg/scene/primitives/trianglemesh/TriangleMesh.h"

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
    static std::shared_ptr<TriangleMesh> createPrimVarFixtureMesh() {
        auto triangleMesh = std::make_shared<crayg::TriangleMesh>();

        triangleMesh->points.emplace_back(0.0f, 0.0f, 0.0f);
        triangleMesh->points.emplace_back(0.0f, 0.0f, 1.0f);
        triangleMesh->points.emplace_back(0.0f, 0.0f, 2.0f);
        triangleMesh->points.emplace_back(1.0f, 0.0f, 0.0f);
        triangleMesh->points.emplace_back(1.0f, 0.0f, 1.0f);
        triangleMesh->points.emplace_back(1.0f, 0.0f, 2.0f);

        triangleMesh->faceVertexIndices.emplace_back(0, 3, 1);
        triangleMesh->faceVertexIndices.emplace_back(1, 3, 4);
        triangleMesh->faceVertexIndices.emplace_back(1, 4, 2);
        triangleMesh->faceVertexIndices.emplace_back(2, 4, 5);

        triangleMesh->init();
        return triangleMesh;
    }

    static std::shared_ptr<TriangleMesh> createSingleTriangle() {
        auto triangleMesh = std::make_shared<crayg::TriangleMesh>();

        triangleMesh->points.emplace_back(0.0f, 0.0f, 0.0f);
        triangleMesh->points.emplace_back(0.0f, 1.0f, 0.0f);
        triangleMesh->points.emplace_back(1.0f, 0.0f, 0.0f);

        triangleMesh->faceVertexIndices.emplace_back(0, 1, 2);

        triangleMesh->init();
        return triangleMesh;
    }
};

}
