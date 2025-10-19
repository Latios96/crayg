#pragma once

#include "crayg/foundation/math/geometry/Vector3f.h"
#include "crayg/scene/primitives/trianglemesh/TriangleMesh.h"

namespace crayg {

template <typename T> class AbstractLightShapeGenerator {
  public:
    AbstractLightShapeGenerator(const T &light);

    virtual int getPointCount() = 0;
    virtual int getIndicesCount() = 0;
    virtual void generateShape(Vector3f *points, TriangleMesh::FaceVertexIndices *indices) = 0;

    virtual ~AbstractLightShapeGenerator() = default;

  protected:
    T light;
};

template <typename T> AbstractLightShapeGenerator<T>::AbstractLightShapeGenerator(const T &light) : light(light) {
}

}
