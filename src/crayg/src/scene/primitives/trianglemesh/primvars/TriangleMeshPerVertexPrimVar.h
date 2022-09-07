#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_TRIANGLEMESHPERVERTEXPRIMVAR_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_TRIANGLEMESHPERVERTEXPRIMVAR_H_

#include <ostream>
#include "TriangleMeshAbstractPrimVar.h"
#include "scene/primitives/trianglemesh/BarycentricCoordinates.h"
#include "utils/ToStringHelper.h"

namespace crayg {

template<typename T>
struct VertexData {
    T v0, v1, v2;
    VertexData() = default;
    explicit VertexData(const T &value) : v0(value), v1(value), v2(value) {}
    VertexData(const T &v0, const T &v1, const T &v2) : v0(v0), v1(v1), v2(v2) {}
    bool operator==(const VertexData &rhs) const {
        return v0 == rhs.v0 &&
            v1 == rhs.v1 &&
            v2 == rhs.v2;
    }
    bool operator!=(const VertexData &rhs) const {
        return !(rhs == *this);
    }
    template<typename OStream>
    friend std::ostream &operator<<(std::ostream &os, const VertexData &data) {
        os << ToStringHelper("VertexData")
            .addMember("v0", data.v0)
            .addMember("v0", data.v1)
            .addMember("v0", data.v2)
            .finish();
        return os;
    }
    virtual ~VertexData() = default;
};

template<typename T>
class TriangleMeshPerVertexPrimVar : public TriangleMeshAbstractPrimVar<T> {
 public:
    explicit TriangleMeshPerVertexPrimVar(TriangleMesh &triangleMesh) : TriangleMeshAbstractPrimVar<T>(
        triangleMesh) {}
    void allocate() override {
        vertexData.resize(this->triangleMesh.faceCount());
    }
    void write(std::size_t faceId, const VertexData<T> &value) {
        vertexData[faceId] = value;
    }
    void write(std::size_t faceId, const T &v0, const T &v1, const T &v2) {
        write(faceId, {v0, v1, v2});
    }
    VertexData<T> read(int pointIndex) {
        return vertexData[pointIndex];
    }
    T interpolateAt(std::size_t faceId, const Vector3f &point) override {
        BarycentricCoordinates coordinates = BarycentricCoordinates(Triangle(&this->triangleMesh, faceId), point);
        VertexData<T> vertexDataForFace = vertexData[faceId];
        return coordinates.interpolateLinear(vertexDataForFace.v0, vertexDataForFace.v1, vertexDataForFace.v2);
    }
    bool operator==(const std::vector<VertexData<T>> &otherVertexData) const {
        return vertexData == otherVertexData;
    }
    bool operator!=(const std::vector<VertexData<T>> &otherVertexData) const {
        return vertexData != otherVertexData;
    }
    template<typename OStream>
    friend std::ostream &operator<<(std::ostream &os, const TriangleMeshPerVertexPrimVar &var) {
        os << ToStringHelper("TriangleMeshPerVertexPrimVar")
            .addMember("vertexData", var.vertexData)
            .finish();
        return os;
    }
    void apply(const std::function<T(T)> func) override {
        for (auto &data: vertexData) {
            data.v0 = func(data.v0);
            data.v1 = func(data.v1);
            data.v2 = func(data.v2);
        }
    }
 private:
    std::vector<VertexData<T>> vertexData;
};
}

#endif //CRAYG_SRC_CRAYG_SRC_SCENE_TRIANGLEMESHPERVERTEXPRIMVAR_H_