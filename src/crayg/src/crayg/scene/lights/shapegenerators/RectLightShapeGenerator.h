#pragma once

#include "AbstractLightShapeGenerator.h"
#include "crayg/scene/lights/RectLight.h"

namespace crayg {

class RectLightShapeGenerator : public AbstractLightShapeGenerator<RectLight> {
  public:
    explicit RectLightShapeGenerator(const RectLight &light);
    int getPointCount() override;
    int getIndicesCount() override;
    void generateShape(Vector3f *points, TriangleMesh::FaceVertexIndices *indices) override;

  private:
    void generatePoints(Vector3f *vertices) const;
    void generateIndices(TriangleMesh::FaceVertexIndices *indices) const;
    static const int POINT_COUNT = 4;
    static const int FACE_COUNT = 2;
};

}