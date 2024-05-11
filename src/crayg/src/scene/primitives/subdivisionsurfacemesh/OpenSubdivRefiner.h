#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_PRIMITIVES_SUBDIVISIONSURFACEMESH_OPENSUBDIVREFINER_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_PRIMITIVES_SUBDIVISIONSURFACEMESH_OPENSUBDIVREFINER_H_

#include "SubdivisionSurfaceMesh.h"
#include <opensubdiv/far/topologyDescriptor.h>
#include <opensubdiv/far/topologyRefiner.h>

namespace crayg {

class OpenSubdivRefiner {
  public:
    explicit OpenSubdivRefiner(SubdivisionSurfaceMesh &subdivisionSurfaceMesh);
    void refine(int maxLevel = 3);

  private:
    SubdivisionSurfaceMesh &subdivisionSurfaceMesh;

    std::unique_ptr<OpenSubdiv::Far::TopologyRefiner> createRefiner();
    OpenSubdiv::Far::TopologyDescriptor createDescriptor();
    void refinePoints(const std::unique_ptr<OpenSubdiv::Far::TopologyRefiner> &refiner, int maxlevel,
                      const OpenSubdiv::Far::TopologyLevel &refLastLevel);
    void refineIndices(const OpenSubdiv::Far::TopologyLevel &refLastLevel);
    void refineNormals(const std::unique_ptr<OpenSubdiv::Far::TopologyRefiner> &refiner,
                       const OpenSubdiv::Far::TopologyLevel &refLastLevel);
    void refineUvs(const std::unique_ptr<OpenSubdiv::Far::TopologyRefiner> &refiner, int maxlevel,
                   const OpenSubdiv::Far::TopologyLevel &refLastLevel);
    OpenSubdiv::Sdc::Options::VtxBoundaryInterpolation getBoundaryInterpolation() const;

    OpenSubdiv::Far::TopologyDescriptor::FVarChannel channels[1];
    std::vector<int> normalsIndices;
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_SCENE_PRIMITIVES_SUBDIVISIONSURFACEMESH_OPENSUBDIVREFINER_H_
