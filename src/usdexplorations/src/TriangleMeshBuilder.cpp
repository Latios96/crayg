//
// Created by Jan on 28.10.2021.
//

#include "TriangleMeshBuilder.h"

namespace crayg {

TriangleMeshBuilder::TriangleMeshBuilder() {
    triangleMesh = std::make_shared<TriangleMesh>();
}
std::vector<Vector3f> &crayg::TriangleMeshBuilder::getPoints() {
    return triangleMesh->points;
}
std::vector<int> &crayg::TriangleMeshBuilder::faceIndices() {
    return triangleMesh->faceIndices;
}
std::shared_ptr<TriangleMesh> TriangleMeshBuilder::build() {
    triangleMesh->init();

    return triangleMesh;
}

}
