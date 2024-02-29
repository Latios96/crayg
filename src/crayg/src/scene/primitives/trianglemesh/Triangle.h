#ifndef CRAYG_TRIANGLE_H
#define CRAYG_TRIANGLE_H

#include "scene/Imageable.h"

namespace crayg {

class TriangleMesh;

class Triangle : public Imageable {
  public:
    Triangle() {
        triangleMesh = nullptr;
        faceId = 0;
        imageableType = ImageableType::TRIANGLE;
    }

    Triangle(TriangleMesh *triangleMesh, std::size_t faceId) : triangleMesh(triangleMesh), faceId(faceId) {
        imageableType = ImageableType::TRIANGLE;
    }

    Triangle(TriangleMesh *triangleMesh, std::size_t faceId, Transform *instanceTransform)
        : Triangle(triangleMesh, faceId) {
        this->instanceTransform = instanceTransform;
        imageableType = ImageableType::TRIANGLE;
    }

    bool isIntersecting(Ray ray) override;
    Imageable::Intersection intersect(Ray ray) override;
    Vector3f getNormal(Vector3f point) override;
    Vector3f getNormal() const;
    BoundingBox getBounds() const override;
    std::shared_ptr<Material> &getMaterial() override;

    Vector3f &v0() const;
    Vector3f &v1() const;
    Vector3f &v2() const;

    TriangleMesh *triangleMesh;
    std::size_t faceId;
    ~Triangle() override = default;

  private:
    Intersection getIntersectionMullerTrumbore(const Ray &ray);
};

}

#endif // CRAYG_TRIANGLE_H
