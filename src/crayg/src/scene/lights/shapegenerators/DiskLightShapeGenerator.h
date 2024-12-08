#pragma once

#include "AbstractLightShapeGenerator.h"
#include "scene/lights/DiskLight.h"

namespace crayg {

class DiskLightShapeGenerator : public AbstractLightShapeGenerator<DiskLight> {
  public:
    explicit DiskLightShapeGenerator(const DiskLight &light);
    DiskLightShapeGenerator(const DiskLight &light, int subdivisions);
    int getPointCount() override;
    int getIndicesCount() override;
    void generateShape(Vector3f *points, TriangleMesh::FaceVertexIndices *indices) override;

  private:
    void generatePoints(Vector3f *vertices) const;
    void generateIndices(TriangleMesh::FaceVertexIndices *indices) const;
    int subdivisions = 64;
};

}