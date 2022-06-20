#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_TRIANGLEMESHABSTRACTPRIMVAR_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_TRIANGLEMESHABSTRACTPRIMVAR_H_
#include "scene/trianglemesh/TriangleMesh.h"

namespace crayg {

template<typename T>
class TriangleMeshAbstractPrimVar {
 public:
    explicit TriangleMeshAbstractPrimVar(TriangleMesh &triangleMesh) : triangleMesh(triangleMesh) {}
    virtual void allocate() = 0;
    virtual T interpolateAt(int faceIndex, const Vector3f &point) = 0;
 protected:
    TriangleMesh &triangleMesh;
};

}
#endif //CRAYG_SRC_CRAYG_SRC_SCENE_TRIANGLEMESHABSTRACTPRIMVAR_H_
