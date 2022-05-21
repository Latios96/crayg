//
// Created by Jan on 28.10.2021.
//

#ifndef CRAYG_SRC_USDEXPLORATIONS_SRC_TRIANGLEMESHBUILDER_H_
#define CRAYG_SRC_USDEXPLORATIONS_SRC_TRIANGLEMESHBUILDER_H_

#include <scene/TriangleMesh.h>
namespace crayg {

class TriangleMeshBuilder {
 public:
    TriangleMeshBuilder();

    std::vector<Vector3f> &getPoints();
    std::vector<int> &faceIndices();
    std::shared_ptr<TriangleMesh> build();
 private:
    std::shared_ptr<TriangleMesh> triangleMesh;
};

}
#endif //CRAYG_SRC_USDEXPLORATIONS_SRC_TRIANGLEMESHBUILDER_H_
