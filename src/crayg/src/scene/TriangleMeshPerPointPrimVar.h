#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_TRIANGLEMESHPERPOINTPRIMVAR_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_TRIANGLEMESHPERPOINTPRIMVAR_H_

#include "TriangleMeshAbstractPrimVar.h"
#include "basics/BarycentricCoordinates.h"

namespace crayg {

template<typename T>
class TriangleMeshPerPointPrimVar : public TriangleMeshAbstractPrimVar<T> {
 public:
    explicit TriangleMeshPerPointPrimVar(TriangleMesh &triangleMesh) : TriangleMeshAbstractPrimVar<T>(
        triangleMesh) {}
    void allocate() override {
        pointData.reserve(this->triangleMesh.points.size());
    }
    void write(int pointIndex, const T &value) {
        pointData[pointIndex] = value;
    }
    T interpolateAt(int faceIndex, const Vector3f &point) override {
        int indexV0 = this->triangleMesh.faceIndices[faceIndex];
        int indexV1 = this->triangleMesh.faceIndices[faceIndex + 1];
        int indexV2 = this->triangleMesh.faceIndices[faceIndex + 2];
        BarycentricCoordinates coordinates = BarycentricCoordinates(Triangle(&this->triangleMesh, faceIndex), point);
        return coordinates.interpolateLinear(pointData[indexV0], pointData[indexV1], pointData[indexV2]);
    }
 private:
    std::vector<T> pointData;
};

} // crayg

#endif //CRAYG_SRC_CRAYG_SRC_SCENE_TRIANGLEMESHPERPOINTPRIMVAR_H_
