#include "DiskLightShapeGenerator.h"

namespace crayg {

DiskLightShapeGenerator::DiskLightShapeGenerator(const DiskLight &light) : AbstractLightShapeGenerator(light) {
}

DiskLightShapeGenerator::DiskLightShapeGenerator(const DiskLight &light, int subdivisions)
    : AbstractLightShapeGenerator(light), subdivisions(subdivisions) {
}

int DiskLightShapeGenerator::getPointCount() {
    return subdivisions + 1;
}

int DiskLightShapeGenerator::getIndicesCount() {
    return subdivisions;
}

void DiskLightShapeGenerator::generateShape(Vector3f *vertices, TriangleMesh::FaceVertexIndices *indices) {
    generatePoints(vertices);
    generateIndices(indices);
}

void DiskLightShapeGenerator::generatePoints(Vector3f *vertices) const {
    const float epsilon = -0.001f;

    const float radius = light.getRadius();

    vertices[0] = Vector3f(0, 0, 0);

    Vector3f pointOnBorder(-radius, 0, epsilon);
    const float stepSize = 360.f / static_cast<float>(subdivisions);

    for (int i = 1; i <= subdivisions; i++) {
        vertices[i] = Transform::withRotation(0, 0, (i - 1) * stepSize).applyForPoint(pointOnBorder);
    }

    for (int i = 0; i < subdivisions + 1; i++) {
        vertices[i] = light.getTransform().applyForPoint(vertices[i]);
    }
}

void DiskLightShapeGenerator::generateIndices(TriangleMesh::FaceVertexIndices *indices) const {
    for (int i = 0; i < subdivisions - 1; i++) {
        const int middlePointIndex = 0;
        const int previousPointIndex = i + 1;
        const int currentPointIndex = i + 2;
        indices[i] = TriangleMesh::FaceVertexIndices(middlePointIndex, previousPointIndex, currentPointIndex);
    }
    indices[subdivisions - 1] = TriangleMesh::FaceVertexIndices(subdivisions - 1, 1, 0);
}

}