#include "RectLightShapeGenerator.h"

namespace crayg {

RectLightShapeGenerator::RectLightShapeGenerator(const RectLight &light) : AbstractLightShapeGenerator(light) {
}

int RectLightShapeGenerator::getPointCount() {
    return POINT_COUNT;
}

int RectLightShapeGenerator::getIndicesCount() {
    return FACE_COUNT;
}

void RectLightShapeGenerator::generateShape(Vector3f *vertices, TriangleMesh::FaceVertexIndices *indices) {
    generatePoints(vertices);
    generateIndices(indices);
}

void RectLightShapeGenerator::generatePoints(Vector3f *vertices) const {
    const float epsilon = -0.001f;

    const float halfWidth = light.getWidth() / 2.f;
    const float halfHeight = light.getHeight() / 2.f;

    vertices[0].x = -halfWidth;
    vertices[0].y = -halfHeight;
    vertices[0].z = epsilon;
    vertices[1].x = -halfWidth;
    vertices[1].y = halfHeight;
    vertices[1].z = epsilon;
    vertices[2].x = halfWidth;
    vertices[2].y = halfHeight;
    vertices[2].z = epsilon;
    vertices[3].x = +halfWidth;
    vertices[3].y = -halfHeight;
    vertices[3].z = epsilon;

    for (int i = 0; i < POINT_COUNT; i++) {
        vertices[i] = light.getTransform().applyForPoint(vertices[i]);
    }
}

void RectLightShapeGenerator::generateIndices(TriangleMesh::FaceVertexIndices *indices) const {
    indices[0].v0 = 2;
    indices[0].v1 = 1;
    indices[0].v2 = 0;
    indices[1].v0 = 3;
    indices[1].v1 = 2;
    indices[1].v2 = 0;
}

}