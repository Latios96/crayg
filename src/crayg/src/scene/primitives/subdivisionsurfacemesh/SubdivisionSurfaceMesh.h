#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_PRIMITIVES_SUBDIVISIONSURFACEMESH_SUBDIVISIONSURFACEMESH_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_PRIMITIVES_SUBDIVISIONSURFACEMESH_SUBDIVISIONSURFACEMESH_H_

#include <optional>
#include "scene/SceneObject.h"
#include "scene/primitives/trianglemesh/TriangleMesh.h"
#include "scene/primitives/trianglemesh/primvars/PrimVarType.h"

namespace crayg {

class SubdivisionSurfaceMesh: public SceneObject {
 public:
    Vector3f getNormal(Vector3f point) override;
    Intersection intersect(Ray ray) override;
    bool isIntersecting(Ray ray) override;
    BoundingBox getBounds() const override;
    std::string getType() override;
    void getPrimitives(std::vector<Imageable *> &target, bool *isOwning) const override;
    size_t primitiveCount() const override;

    void tessellate();
    std::size_t faceCount() const;

    std::vector<Vector3f> points;
    std::vector<int> faceVertexIndices;
    std::vector<int> faceVertexCounts;

    std::vector<Vector3f> normals;

    enum BoundaryInterpolation {
        EDGE_ONLY,
        EDGE_AND_CORNER
    };

    BoundaryInterpolation boundaryInterpolation = EDGE_ONLY;

    TriangleMesh triangleMesh;
 private:
    bool isTessellated = false;
    void verifyIsTessellated() const;
    void copyNormalsToTriangleMesh();
};

} // crayg

#endif //CRAYG_SRC_CRAYG_SRC_SCENE_PRIMITIVES_SUBDIVISIONSURFACEMESH_SUBDIVISIONSURFACEMESH_H_
