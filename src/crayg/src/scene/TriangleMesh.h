//
// Created by Jan Honsbrok on 13.11.18.
//

#ifndef CRAYG_TRIANGEMESH_H
#define CRAYG_TRIANGEMESH_H

#include <vector>
#include <foundation/BoundingBox.h>
#include "SceneObject.h"
#include "Triangle.h"

class TriangleMesh : public SceneObject {
 public:
    static void createCube(TriangleMesh &mesh);
    Intersection intersect(Ray ray) override;
    bool isIntersecting(Ray ray) override;

    void serialize(Serializer &serializer) override;

    void deserialize(Deserializer &deserializer) override;

    Vector3f getNormal(Vector3f point) override;

    std::vector<Vector3f> points;
    std::vector<int> faceIndexes;
    // todo replace with iterator
    void getTriangles(std::vector<Triangle> &triangles);

    void beforeRender() override;
 private:
    std::vector<Triangle> triangles;
    BoundingBox boundingBox;
};

#endif //CRAYG_TRIANGEMESH_H
