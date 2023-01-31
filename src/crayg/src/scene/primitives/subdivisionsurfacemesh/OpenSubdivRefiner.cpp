#include "OpenSubdivRefiner.h"
#include <opensubdiv/far/topologyRefinerFactory.h>
#include <opensubdiv/far/primvarRefiner.h>

namespace crayg {

class OsdVector3fAdapter: public Vector3f{
 public:
    OsdVector3fAdapter():Vector3f(){}
    OsdVector3fAdapter(const Vector3f &src): Vector3f(src){}
    void Clear( void * =0 ) {
        x=0;
        y=0;
        z=0;
    }

    void AddWithWeight(OsdVector3fAdapter const & src, float weight) {
        x+=weight*src.x;
        y+=weight*src.y;
        z+=weight*src.z;
    }
};

OpenSubdivRefiner::OpenSubdivRefiner(SubdivisionSurfaceMesh &subdivisionSurfaceMesh) : subdivisionSurfaceMesh(
    subdivisionSurfaceMesh) {}

void OpenSubdivRefiner::refine(int maxLevel) {
    auto refiner = createRefiner();

    refiner->RefineUniform(OpenSubdiv::Far::TopologyRefiner::UniformOptions(maxLevel));

    OpenSubdiv::Far::TopologyLevel const & refLastLevel = refiner->GetLevel(maxLevel);

    refinePoints(refiner, maxLevel, refLastLevel);
    refineIndices(refLastLevel);
}

void OpenSubdivRefiner::refinePoints(const std::unique_ptr<OpenSubdiv::Far::TopologyRefiner> &refiner,
                                     int maxlevel,
                                     const OpenSubdiv::Far::TopologyLevel &refLastLevel) {
    std::vector<Vector3f> subdividedPoints(refiner->GetNumVerticesTotal()); // todo use original points
    for(int i=0; i< subdivisionSurfaceMesh.points.size(); i++){
        subdividedPoints[i] = subdivisionSurfaceMesh.points[i];
    }

    OpenSubdiv::Far::PrimvarRefiner primvarRefiner(*refiner);

    auto *src = static_cast<OsdVector3fAdapter *>(subdividedPoints.data());
    for (int level = 1; level <= maxlevel; ++level) {
        OsdVector3fAdapter * dst = src + refiner->GetLevel(level-1).GetNumVertices();
        primvarRefiner.Interpolate(level, src, dst);
        src = dst;
    }

    subdivisionSurfaceMesh.points.resize(refLastLevel.GetNumVertices());
    int firstOfLastVerts = refiner->GetNumVerticesTotal() - refLastLevel.GetNumVertices();
    for(int i=0;i<refLastLevel.GetNumVertices();i++){
        subdivisionSurfaceMesh.points[i] = subdividedPoints[firstOfLastVerts+i];
    }
}

void OpenSubdivRefiner::refineIndices(const OpenSubdiv::Far::TopologyLevel &refLastLevel) {
    std::vector<int> newFaceVertexIndices;
    const int numberOfFaces = refLastLevel.GetNumFaces();
    std::vector<int> newFaceVertexCounts;

    for (int face = 0; face < numberOfFaces; face++) {
        OpenSubdiv::Far::ConstIndexArray fverts = refLastLevel.GetFaceVertices(face);
        newFaceVertexCounts.push_back(fverts.size());
        for (int fvert : fverts) {
            newFaceVertexIndices.push_back(fvert);
        }
    }

    subdivisionSurfaceMesh.faceVertexIndices = newFaceVertexIndices;// TODO is this needed? Or can we just push back directly in the original vector
    subdivisionSurfaceMesh.faceVertexCounts = newFaceVertexCounts;
}
std::unique_ptr<OpenSubdiv::Far::TopologyRefiner> OpenSubdivRefiner::createRefiner() {
    auto descriptor = createDescriptor();

    OpenSubdiv::Sdc::SchemeType type = OpenSubdiv::Sdc::SCHEME_CATMARK;

    OpenSubdiv::Sdc::Options options;
    options.SetVtxBoundaryInterpolation(OpenSubdiv::Sdc::Options::VTX_BOUNDARY_EDGE_ONLY);

    auto refiner = OpenSubdiv::v3_4_4::Far::TopologyRefinerFactory<OpenSubdiv::Far::TopologyDescriptor>::Create(descriptor,
                                                                                                                OpenSubdiv::v3_4_4::Far::TopologyRefinerFactory<
                                                                                                                    OpenSubdiv::Far::TopologyDescriptor>::Options(
                                                                                                                    type,
                                                                                                                    options));
    return std::unique_ptr<OpenSubdiv::Far::TopologyRefiner>(refiner);
}
OpenSubdiv::Far::TopologyDescriptor OpenSubdivRefiner::createDescriptor() {
    OpenSubdiv::Far::TopologyDescriptor descriptor;
    descriptor.numVertices = subdivisionSurfaceMesh.points.size();
    descriptor.numFaces = subdivisionSurfaceMesh.faceCount();
    descriptor.numVertsPerFace = subdivisionSurfaceMesh.faceVertexCounts.data();
    descriptor.vertIndicesPerFace = subdivisionSurfaceMesh.faceVertexIndices.data(); // TODO check for clockwise/counter-clockwise
    return descriptor;
}
} // crayg