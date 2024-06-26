#pragma once

#include "PrimVarType.h"
#include "basics/Vector3f.h"

class TriangleMesh;

namespace crayg {

template <typename T> class TriangleMeshAbstractPrimVar {
  public:
    explicit TriangleMeshAbstractPrimVar(TriangleMesh &triangleMesh) : triangleMesh(triangleMesh) {
    }

    virtual void allocate() = 0;
    virtual T interpolateAt(std::size_t faceId, const Vector3f &point) = 0;
    virtual void apply(const std::function<T(T)> func) = 0;
    virtual PrimVarType getType() = 0;
    virtual ~TriangleMeshAbstractPrimVar() = default;

  protected:
    TriangleMesh &triangleMesh;
};

}
