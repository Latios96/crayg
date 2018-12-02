//
// Created by Jan Honsbrok on 13.11.18.
//

#include "TriangeMesh.h"

bool TriangleMesh::isIntersecting(Ray ray){
    return false;
}

Imageable::Intersection TriangleMesh::intersect(Ray ray) {

    Imageable::Intersection hitIntersection(std::numeric_limits<float>::max(), nullptr);

    for (Triangle &triangle : triangles){
        Imageable::Intersection intersection = triangle.intersect(ray);
        if (intersection.rayParameter < hitIntersection.rayParameter){
            hitIntersection = intersection;
        }
    }
    return hitIntersection;
}

void TriangleMesh::getTriangles(std::vector<Triangle> &triangles) {
    Vector3f transform = getPosition();
    for(int i=0; i<faceIndexes.size(); i=i+3){
        const Vector3f v0 = points[faceIndexes[i]] + transform;
        const Vector3f v1 = points[faceIndexes[i + 1]] + transform;
        const Vector3f v2 = points[faceIndexes[i + 2]] + transform;
        triangles.push_back({v0, v1, v2});
    }
}

void TriangleMesh::serialize(Serializer &serializer) {
    SceneObject::serialize(serializer);
    serializer.writeVector3fArray("points", points);
    serializer.writeIntArray("faceIndexes", faceIndexes);
}

void TriangleMesh::deserialize(Deserializer &deserializer) {
    SceneObject::deserialize(deserializer);
    deserializer.readVector3fArray("points", points);
    deserializer.readIntArray("faceIndexes", faceIndexes);
}

Vector3f TriangleMesh::getNormal(Vector3f point) {
    return Vector3f(0,1,0);
}

void TriangleMesh::createCube(TriangleMesh &mesh) {
    mesh.points.push_back({-1, -1, 1});
    mesh.points.push_back({-1, -1, 1});
    mesh.points.push_back({-1, 1, 1});
    mesh.points.push_back({1, 1, 1});
    mesh.points.push_back({-1, 1, -1});
    mesh.points.push_back({1, 1, -1});
    mesh.points.push_back({-1, -1, -1});
    mesh.points.push_back({1, -1, -1});

    mesh.faceIndexes.push_back(0);
    mesh.faceIndexes.push_back(1);
    mesh.faceIndexes.push_back(2);

    mesh.faceIndexes.push_back(2);
    mesh.faceIndexes.push_back(1);
    mesh.faceIndexes.push_back(3);

    mesh.faceIndexes.push_back(2);
    mesh.faceIndexes.push_back(3);
    mesh.faceIndexes.push_back(4);
    mesh.faceIndexes.push_back(4);
    mesh.faceIndexes.push_back(3);
    mesh.faceIndexes.push_back(5);
    mesh.faceIndexes.push_back(4);
    mesh.faceIndexes.push_back(5);
    mesh.faceIndexes.push_back(6);
    mesh.faceIndexes.push_back(6);
    mesh.faceIndexes.push_back(5);
    mesh.faceIndexes.push_back(7);
    mesh.faceIndexes.push_back(6);
    mesh.faceIndexes.push_back(7);
    mesh.faceIndexes.push_back(0);
    mesh.faceIndexes.push_back(0);
    mesh.faceIndexes.push_back(7);
    mesh.faceIndexes.push_back(1);
    mesh.faceIndexes.push_back(1);
    mesh.faceIndexes.push_back(7);
    mesh.faceIndexes.push_back(3);
    mesh.faceIndexes.push_back(3);
    mesh.faceIndexes.push_back(7);
    mesh.faceIndexes.push_back(5);
    mesh.faceIndexes.push_back(6);
    mesh.faceIndexes.push_back(0);
    mesh.faceIndexes.push_back(4);
    mesh.faceIndexes.push_back(4);
    mesh.faceIndexes.push_back(0);
    mesh.faceIndexes.push_back(2);
}

void TriangleMesh::beforeRender() {
    Imageable::beforeRender();
    getTriangles(triangles);
}
