//
// Created by Jan Honsbrok on 13.11.18.
//

#ifndef CRAYG_TRIANGEMESH_H
#define CRAYG_TRIANGEMESH_H

#include <vector>
#include <basics/BoundingBox.h>
#include "SceneObject.h"
#include "Triangle.h"

namespace crayg {

class TriangleMesh : public SceneObject {
 public:
    static void createCube(TriangleMesh &mesh);
    Intersection intersect(Ray ray) override;
    bool isIntersecting(Ray ray) override;
    BoundingBox getBounds() const override;

    Vector3f getNormal(Vector3f point) override;

    std::vector<Vector3f> points;
    std::vector<Vector3f> normals;
    std::vector<int> faceIndices;
    void getTriangles(std::vector<std::shared_ptr<Imageable>> &triangles);
    friend class Triangle;
    void init();
    std::string getType() override;
 private:
    BoundingBox boundingBox;
    void createBounds();
    void createNormals();
};

}

#endif //CRAYG_TRIANGEMESH_H
