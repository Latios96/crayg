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
    for (Triangle triangle : triangles){
        Ray intersectionRay = triangle.intersect(ray);
        if (intersectionRay.isValid()){
            return intersectionRay;
        }
    }
    return Ray::createInvalid();
}

void TriangleMesh::getTriangles(std::vector<Triangle> &triangles) {
    for(int i=0; i<faceIndexes.size(); i=i+3){
        triangles.push_back({points[faceIndexes[i]], points[faceIndexes[i+1]], points[faceIndexes[i+2]]});
    }
}

void TriangleMesh::serialize(Serializer &serializer) {
    SceneObject::serialize(serializer);
}

void TriangleMesh::deserialize(Deserializer &deserializer) {
    SceneObject::deserialize(deserializer);
}

Vector3f TriangleMesh::getNormal(Vector3f point) {
    return Vector3f(0,1,0);
}
