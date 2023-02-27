#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_TRIANGLEMESHPERFACEPRIMVAR_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_TRIANGLEMESHPERFACEPRIMVAR_H_

#include "TriangleMeshAbstractPrimVar.h"
#include "scene/primitives/trianglemesh/BarycentricCoordinates.h"
#include "utils/ToStringHelper.h"
#include <ostream>

namespace crayg {

template <typename T> class TriangleMeshPerFacePrimVar : public TriangleMeshAbstractPrimVar<T> {
  public:
    explicit TriangleMeshPerFacePrimVar(TriangleMesh &triangleMesh) : TriangleMeshAbstractPrimVar<T>(triangleMesh) {
    }

    void allocate() override {
        faceData.resize(this->triangleMesh.faceCount());
    }

    void write(std::size_t faceId, const T &value) {
        faceData[faceId] = value;
    }

    T read(std::size_t faceId) {
        return faceData[faceId];
    }

    T interpolateAt(std::size_t faceId, const Vector3f &point) override {
        return faceData[faceId];
    }

    bool operator==(const std::vector<T> &otherfaceData) const {
        return faceData == otherfaceData;
    }

    bool operator!=(const std::vector<T> &otherfaceData) const {
        return faceData != otherfaceData;
    }

    template <typename OStream>
    friend std::ostream &operator<<(std::ostream &os, const TriangleMeshPerFacePrimVar &var) {
        os << ToStringHelper("TriangleMeshPerFacePrimVar").addMember("faceData", var.faceData).finish();
        return os;
    }

    void apply(const std::function<T(T)> func) override {
        for (auto &data : faceData) {
            data = func(data);
        }
    }

    PrimVarType getType() override {
        return PER_FACE;
    }

  private:
    std::vector<T> faceData;
};
}

#endif // CRAYG_SRC_CRAYG_SRC_SCENE_TRIANGLEMESHPERFACEPRIMVAR_H_
