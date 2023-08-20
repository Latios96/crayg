#ifndef CRAYG_TRIANGEMESH_H
#define CRAYG_TRIANGEMESH_H

#include "Triangle.h"
#include "basics/BoundingBox.h"
#include "scene/SceneObject.h"
#include "scene/primitives/trianglemesh/primvars/TriangleMeshAbstractPrimVar.h"
#include <ostream>
#include <vector>

namespace crayg {

class TriangleMesh : public SceneObject {
  public:
    TriangleMesh();
    static void createCube(TriangleMesh &mesh);
    Intersection intersect(Ray ray) override;
    bool isIntersecting(Ray ray) override;
    BoundingBox getBounds() const override;
    Vector3f getNormal(Vector3f point) override;
    void getPrimitives(std::vector<Imageable *> &target, bool *isOwning) const override;
    std::size_t primitiveCount() const override;
    friend class Triangle;
    void init();
    std::string getType() override;
    std::size_t faceCount() const;

    template <typename T> T *addNormalsPrimVar();

    template <typename T> T *getNormalsPrimVarAs();

    template <typename T> T *addUvsPrimVar();

    template <typename T> T *getUvsPrimVarAs();

    std::vector<Vector3f> points;
    std::unique_ptr<TriangleMeshAbstractPrimVar<Vector3f>> normalsPrimVar = nullptr;
    std::unique_ptr<TriangleMeshAbstractPrimVar<Vector2f>> uvsPrimVar = nullptr;

    struct FaceVertexIndices {
        int v0, v1, v2;
        FaceVertexIndices(int v0, int v1, int v2);
        bool operator==(const FaceVertexIndices &rhs) const;
        bool operator!=(const FaceVertexIndices &rhs) const;
        friend std::ostream &operator<<(std::ostream &os, const FaceVertexIndices &indices);
    };

    std::vector<FaceVertexIndices> faceVertexIndices;

    class FaceIdIterator {
      public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = std::size_t;
        using difference_type = std::size_t;
        using pointer = std::size_t *;
        using reference = std::size_t &;

        FaceIdIterator(std::size_t id) : id(id) {
        }

        FaceIdIterator operator++();
        std::size_t operator*() const;
        bool operator!=(const FaceIdIterator &o) const;
        ;

      private:
        std::size_t id;
    };

    class FaceIdIteratorAdapter {
      public:
        FaceIdIteratorAdapter(TriangleMesh &triangleMesh) : triangleMesh(triangleMesh) {
        }

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

template <typename T> T *TriangleMesh::addNormalsPrimVar() {
    normalsPrimVar = std::make_unique<T>(*this);
    normalsPrimVar->allocate();
    return getNormalsPrimVarAs<T>();
}

template <typename T> T *TriangleMesh::getNormalsPrimVarAs() {
    return dynamic_cast<T *>(normalsPrimVar.get());
}

template <typename T> T *TriangleMesh::addUvsPrimVar() {
    uvsPrimVar = std::make_unique<T>(*this);
    uvsPrimVar->allocate();
    return getUvsPrimVarAs<T>();
}

template <typename T> T *TriangleMesh::getUvsPrimVarAs() {
    return dynamic_cast<T *>(uvsPrimVar.get());
}

}

#endif // CRAYG_TRIANGEMESH_H
