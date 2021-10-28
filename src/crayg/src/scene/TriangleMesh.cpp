//
// Created by Jan Honsbrok on 13.11.18.
//

#include "TriangleMesh.h"

namespace crayg {

bool TriangleMesh::isIntersecting(Ray ray) {
    return false;
}

Imageable::Intersection TriangleMesh::intersect(Ray ray) {
    if (boundingBox.isIntersecting(ray)) {
        Imageable::Intersection hitIntersection(std::numeric_limits<float>::max(), nullptr);

        for (int i = 0; i < faceIndexes.size(); i = i + 3) {
            Triangle triangle(this, i);
            Imageable::Intersection intersection = triangle.intersect(ray);
            hitIntersection = Imageable::Intersection::nearest(intersection, hitIntersection);
        }
        return hitIntersection;
    } else {
        return {std::numeric_limits<float>::max(), nullptr};
    }
}

void TriangleMesh::getTriangles(std::vector<std::shared_ptr<Imageable>> &triangles) {
    for (int i = 0; i < faceIndexes.size(); i = i + 3) {
        triangles.push_back(std::make_shared<Triangle>(this, i));
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
    return {0, 1, 0};
}

void TriangleMesh::createCube(TriangleMesh &mesh) {
    mesh.points.emplace_back(-1, -1, 1);
    mesh.points.emplace_back(-1, -1, 1);
    mesh.points.emplace_back(-1, 1, 1);
    mesh.points.emplace_back(1, 1, 1);
    mesh.points.emplace_back(-1, 1, -1);
    mesh.points.emplace_back(1, 1, -1);
    mesh.points.emplace_back(-1, -1, -1);
    mesh.points.emplace_back(1, -1, -1);

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


void TriangleMesh::createBounds() {
    Vector3f min, max;
    for (const auto &point : points) {
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
void TriangleMesh::createNormals() {
    normals.resize(points.size());
    for (int i = 0; i < faceIndexes.size(); i = i + 3) {
        Triangle triangle(this, i);
        Vector3f normal = triangle.getNormal();
        const int x = faceIndexes[triangle.faceIndex];
        normals[x] = normals[x].add(normal);
        normals[faceIndexes[triangle.faceIndex + 1]] = normals[faceIndexes[triangle.faceIndex + 1]].add(normal);
        normals[faceIndexes[triangle.faceIndex + 2]] = normals[faceIndexes[triangle.faceIndex + 2]].add(normal);
    }
    for (auto &normal: normals) {
        normal = normal.normalize();
    }
}
BoundingBox TriangleMesh::getBounds() const {
    return boundingBox;
}
void TriangleMesh::init() {
    for (auto &point: points) {
        point = transform.apply(point);
    } // todo check if this is necessary
    createBounds();
    createNormals();
}

}
