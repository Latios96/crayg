//
// Created by Jan Honsbrok on 13.11.18.
//

#include "TriangleMesh.h"

bool TriangleMesh::isIntersecting(Ray ray) {
    return false;
}

Imageable::Intersection TriangleMesh::intersect(Ray ray) {
    if (boundingBox.isIntersecting(ray)) {
        Imageable::Intersection hitIntersection(std::numeric_limits<float>::max(), nullptr);

        for (std::shared_ptr<Triangle> &triangle : triangles) {
            Imageable::Intersection intersection = triangle->intersect(ray);
            if (intersection.rayParameter < hitIntersection.rayParameter) {
                hitIntersection = intersection;
            }
        }
        return hitIntersection;
    } else {
        return {std::numeric_limits<float>::max(), nullptr};
    }
}

void TriangleMesh::getTriangles(std::vector<std::shared_ptr<Triangle>> &triangles) {

    for (int i = 0; i < faceIndexes.size(); i = i + 3) {
        Vector3f v0 = points[faceIndexes[i]];
        Vector3f v1 = points[faceIndexes[i + 1]];
        Vector3f v2 = points[faceIndexes[i + 2]];
        triangles.push_back(std::make_shared<Triangle>(v0, v1, v2));
    }
}

void TriangleMesh::serialize(Serializer &serializer) {
    SceneObject::serialize(serializer);
    serializer.writeType("TriangleMesh");
    serializer.writeVector3fArray("points", points);
    serializer.writeIntArray("faceIndexes", faceIndexes);
}

void TriangleMesh::deserialize(Deserializer &deserializer) {
    SceneObject::deserialize(deserializer);
    deserializer.readVector3fArray("points", points);
    deserializer.readIntArray("faceIndexes", faceIndexes);
}

Vector3f TriangleMesh::getNormal(Vector3f point) {
    return Vector3f(0, 1, 0);
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
    Vector3f min, max;
    for (int i = 0; i < points.size(); i++) {
        Vector3f point = points[i];
        if (point.x < min.x) {
            min.x = point.x;
        }
        if (point.y < min.y) {
            min.y = point.y;
        }
        if (point.z < min.z) {
            min.z = point.z;
        }

        if (point.x > max.x) {
            max.x = point.x;
        }
        if (point.y > max.y) {
            max.y = point.y;
        }
        if (point.z > max.z) {
            max.z = point.z;
        }
    }
    boundingBox = BoundingBox(min, max);
}


