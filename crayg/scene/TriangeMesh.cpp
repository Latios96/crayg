//
// Created by Jan Honsbrok on 13.11.18.
//

#include "TriangeMesh.h"

bool TriangleMesh::intersects(Ray ray) {
    return false;
}

Ray TriangleMesh::intersect(Ray ray) {
    std::vector<Triangle> triangles;
    getTriangles(triangles);

    Ray hitRay = Ray::createInvalid();

    for (Triangle triangle : triangles){
        Ray intersectionRay = triangle.intersect(ray);
        if (intersectionRay.length < hitRay.length){
            hitRay = intersectionRay;
        }
    }
    return hitRay;
}

void TriangleMesh::getTriangles(std::vector<Triangle> &triangles) {
    for(int i=0; i<faceIndexes.size(); i=i+3){
        triangles.push_back({points[faceIndexes[i]], points[faceIndexes[i+1]], points[faceIndexes[i+2]]});
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