#pragma once

#include "TriangleMeshAbstractPrimVar.h"
#include "scene/primitives/trianglemesh/BarycentricCoordinates.h"
#include "utils/ToStringHelper.h"
#include <fmt/ostream.h>

namespace crayg {

template <typename T> class TriangleMeshPerPointPrimVar : public TriangleMeshAbstractPrimVar<T> {
  public:
    explicit TriangleMeshPerPointPrimVar(TriangleMesh &triangleMesh) : TriangleMeshAbstractPrimVar<T>(triangleMesh) {
    }

    void allocate() override {
        pointData.resize(this->triangleMesh.points.size());
    }

    void write(int pointIndex, const T &value) {
        pointData[pointIndex] = value;
    }

    T read(int pointIndex) {
        return pointData[pointIndex];
    }

    T interpolateAt(std::size_t faceId, const Vector3f &point) override {
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

    template <typename OStream>
    friend std::ostream &operator<<(std::ostream &os, const TriangleMeshPerPointPrimVar<T> &var) {
        os << ToStringHelper("TriangleMeshPerPointPrimVar").addMember("pointData", var.pointData).finish();
        return os;
    }

    void apply(const std::function<T(T)> func) override {
        for (auto &data : pointData) {
            data = func(data);
        }
    }

    PrimVarType getType() override {
        return PrimVarType::PER_POINT;
    }

    virtual ~TriangleMeshPerPointPrimVar() = default;

  private:
    std::vector<T> pointData;
};

} // crayg

template <typename T> struct fmt::formatter<crayg::TriangleMeshPerPointPrimVar<T>> : ostream_formatter {};
