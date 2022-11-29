#ifndef CRAYG_TRIANGEMESH_H
#define CRAYG_TRIANGEMESH_H

#include <vector>
#include "basics/BoundingBox.h"
#include "scene/SceneObject.h"
#include "Triangle.h"
#include "scene/primitives/trianglemesh/primvars/TriangleMeshAbstractPrimVar.h"

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
    void getPrimitives(std::vector<Imageable *> &target, bool *isOwning) const override;
    friend class Triangle;
    void init();
    std::string getType() override;
    int faceCount() const;

    template<typename T>
    T *addNormalsPrimVar();

    template<typename T>
    T *getNormalsPrimVarAs();

    std::vector<Vector3f> points;
    std::unique_ptr<TriangleMeshAbstractPrimVar<Vector3f>> normalsPrimVar = nullptr;

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

        FaceIdIterator operator++();
        std::size_t operator*() const;
        bool operator!=(const FaceIdIterator &o) const;;
     private:
        std::size_t id;
    };

    class FaceIdIteratorAdapter {
     public:
        FaceIdIteratorAdapter(TriangleMesh &triangleMesh) : triangleMesh(triangleMesh) {}

        FaceIdIterator begin();
        FaceIdIterator end();
     private:
        TriangleMesh &triangleMesh;
    };

    FaceIdIteratorAdapter faceIds() const;

 private:
    BoundingBox boundingBox;
    void createBounds();
    void createNormals();
};

template<typename T>
T *TriangleMesh::addNormalsPrimVar() {
    normalsPrimVar = std::make_unique<T>(*this);
    normalsPrimVar->allocate();
    return getNormalsPrimVarAs<T>();
}

template<typename T>
T *TriangleMesh::getNormalsPrimVarAs() {
    return dynamic_cast<T *>(normalsPrimVar.get());
}

}

#endif //CRAYG_TRIANGEMESH_H
