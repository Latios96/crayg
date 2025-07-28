#pragma once

#include "scene/SceneObject.h"
#include "scene/primitives/trianglemesh/TriangleMesh.h"
#include "scene/primitives/trianglemesh/primvars/PrimVarType.h"
#include <optional>

namespace crayg {

class SubdivisionSurfaceMesh : public SceneObject {
  public:
    Vector3f getNormal(Vector3f point) override;
    Intersection intersect(Ray ray) override;
    bool isIntersecting(Ray ray) override;
    BoundingBox getBounds() const override;
    std::string getType() override;
    void getPrimitives(std::vector<Imageable *> &target) const override;
    size_t primitiveCount() const override;

    void tessellate();
    bool isTesselated() const;
    bool hasUvs() const;
    std::size_t faceCount() const;

    std::vector<Vector3f> points;
    std::vector<int> faceVertexIndices;
    std::vector<int> faceVertexCounts;

    std::vector<Vector3f> normals;

    std::vector<Vector2f> uvs;
    std::vector<int> uvIndices;

    enum class BoundaryInterpolation { EDGE_ONLY, EDGE_AND_CORNER };

    BoundaryInterpolation boundaryInterpolation = BoundaryInterpolation::EDGE_ONLY;
    int maxSubdivision = 3;
    TriangleMesh triangleMesh;

  private:
    bool isTessellated = false;
    void verifyIsTessellated() const;
    void copyNormalsToTriangleMesh();
    void copyUvsToTriangleMesh();
};

}
