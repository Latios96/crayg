#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_TRIANGLEMESHPERVERTEXPRIMVAR_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_TRIANGLEMESHPERVERTEXPRIMVAR_H_

#include "TriangleMeshAbstractPrimVar.h"

namespace crayg {

template<typename T>
struct VertexData {
    T v0, v1, v2;
    VertexData() = default;
    explicit VertexData(const T &value) : v0(value), v1(value), v2(value) {}
    VertexData(const T &v0, const T &v1, const T &v2) : v0(v0), v1(v1), v2(v2) {}
};

template<typename T>
class TriangleMeshPerVertexPrimVar : public TriangleMeshAbstractPrimVar<T> {
 public:
    explicit TriangleMeshPerVertexPrimVar(TriangleMesh &triangleMesh) : TriangleMeshAbstractPrimVar<T>(
        triangleMesh) {}
    void allocate() override {
        vertexData.resize(this->triangleMesh.faceCount());
    }
    void write(int faceId, const VertexData<T> &value) {
        vertexData[faceId] = value;
    }
    void write(int faceId, const T &v0, const T &v1, const T &v2) {
        write(faceId, {v0, v1, v2});
    }
    T interpolateAt(int faceId, const Vector3f &point) override {
        BarycentricCoordinates coordinates = BarycentricCoordinates(Triangle(&this->triangleMesh, faceId), point);
        VertexData<T> vertexDataForFace = vertexData[faceId];
        return coordinates.interpolateLinear(vertexDataForFace.v0, vertexDataForFace.v1, vertexDataForFace.v2);
    }
 private:
    std::vector<VertexData<T>> vertexData;
};
}

#endif //CRAYG_SRC_CRAYG_SRC_SCENE_TRIANGLEMESHPERVERTEXPRIMVAR_H_
