//
// Created by Jan Honsbrok on 13.11.18.
//

#ifndef CRAYG_TRIANGEMESH_H
#define CRAYG_TRIANGEMESH_H

#include <vector>
#include <basics/BoundingBox.h>
#include "SceneObject.h"
#include "Triangle.h"
#include "TriangleMeshPerPointPrimVar.h"

namespace crayg {

class TriangleMesh : public SceneObject {
 public:
    TriangleMesh();
    static void createCube(TriangleMesh &mesh);
    Intersection intersect(Ray ray) override;
    bool isIntersecting(Ray ray) override;
    BoundingBox getBounds() const override;
    Vector3f getNormal(Vector3f point) override;
    void getTriangles(std::vector<std::shared_ptr<Imageable>> &triangles);
    friend class Triangle;
    void init();
    std::string getType() override;
    int faceCount();

    template<typename T>
    void addNormalsPrimVar() {
        normalsPrimVar = std::make_unique<T>(*this);
        normalsPrimVar->allocate();
    }

    std::vector<Vector3f> points;
    std::unique_ptr<TriangleMeshPerPointPrimVar<Vector3f>> normalsPrimVar = nullptr;

    struct FaceVertexIndices {
        int v0, v1, v2;
        FaceVertexIndices(int v0, int v1, int v2);
        bool operator==(const FaceVertexIndices &rhs) const;
        bool operator!=(const FaceVertexIndices &rhs) const;
    };
    std::vector<FaceVertexIndices> faceVertexIndices;

    class FaceIdIterator {
     public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = std::size_t;
        using difference_type = std::size_t;
        using pointer = std::size_t *;
        using reference = std::size_t &;

        FaceIdIterator(std::size_t id) : id(id) {}

        FaceIdIterator &operator++() {
            return FaceIdIterator(++id);
        }
        std::size_t operator*() const { return id; }
        bool operator!=(const FaceIdIterator &o) const {
            return id != o.id;
        };
     private:
        std::size_t id;
    };

    class FaceIdIteratorAdapter {
     public:
        FaceIdIteratorAdapter(TriangleMesh &triangleMesh) : triangleMesh(triangleMesh) {}

        FaceIdIterator begin() {
            return {0};
        }
        FaceIdIterator end() {
            return {triangleMesh.faceVertexIndices.size()};
        }
     private:
        TriangleMesh &triangleMesh;
    };

    FaceIdIteratorAdapter faceIds() {
        return {*this};
    }

 private:
    BoundingBox boundingBox;
    void createBounds();
    void createNormals();
};

}

#endif //CRAYG_TRIANGEMESH_H
