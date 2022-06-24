#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_TRIANGLEMESHPERPOINTPRIMVAR_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_TRIANGLEMESHPERPOINTPRIMVAR_H_

#include "TriangleMeshAbstractPrimVar.h"
#include "basics/BarycentricCoordinates.h"
#include "utils/ToStringHelper.h"

namespace crayg {

template<typename T>
class TriangleMeshPerPointPrimVar : public TriangleMeshAbstractPrimVar<T> {
 public:
    explicit TriangleMeshPerPointPrimVar(TriangleMesh &triangleMesh) : TriangleMeshAbstractPrimVar<T>(
        triangleMesh) {}
    void allocate() override {
        pointData.resize(this->triangleMesh.points.size());
    }
    void write(int pointIndex, const T &value) {
        pointData[pointIndex] = value;
    }
    T read(int pointIndex) {
        return pointData[pointIndex];
    }
    T interpolateAt(int faceId, const Vector3f &point) override {
        int indexV0 = this->triangleMesh.faceVertexIndices[faceId].v0;
        int indexV1 = this->triangleMesh.faceVertexIndices[faceId].v1;
        int indexV2 = this->triangleMesh.faceVertexIndices[faceId].v2;
        BarycentricCoordinates coordinates = BarycentricCoordinates(Triangle(&this->triangleMesh, faceId), point);
        return coordinates.interpolateLinear(pointData[indexV0], pointData[indexV1], pointData[indexV2]);
    }
    bool operator==(const std::vector<T> &otherPointData) const {
        return pointData == otherPointData;
    }
    bool operator!=(const std::vector<T> &otherPointData) const {
        return pointData != otherPointData;
    }
    template<typename OStream>
    friend std::ostream &operator<<(std::ostream &os, const TriangleMeshPerPointPrimVar &var) {
        os << ToStringHelper("TriangleMeshPerPointPrimVar")
            .addMember("pointData", var.pointData)
            .finish();
        return os;
    }
    virtual ~TriangleMeshPerPointPrimVar() = default;
 private:
    std::vector<T> pointData;
};

} // crayg

#endif //CRAYG_SRC_CRAYG_SRC_SCENE_TRIANGLEMESHPERPOINTPRIMVAR_H_
