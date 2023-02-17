#include "OpenSubdivRefiner.h"
#include <opensubdiv/far/topologyRefinerFactory.h>
#include <opensubdiv/far/primvarRefiner.h>

namespace crayg {

class OsdVector3fAdapter : public Vector3f {
 public:
    OsdVector3fAdapter() : Vector3f() {}
    OsdVector3fAdapter(const Vector3f &src) : Vector3f(src) {}
    void Clear(void * = 0) {
        x = 0;
        y = 0;
        z = 0;
    }

    void AddWithWeight(OsdVector3fAdapter const &src, float weight) {
        x += weight * src.x;
        y += weight * src.y;
        z += weight * src.z;
    }
};

void interpolatePerPoint(const std::unique_ptr<OpenSubdiv::Far::TopologyRefiner> &refiner,
                         int maxlevel,
                         const OpenSubdiv::Far::PrimvarRefiner &primvarRefiner,
                         OsdVector3fAdapter *src) {
    for (int level = 1; level <= maxlevel; ++level) {
        OsdVector3fAdapter *dst = src + refiner->GetLevel(level - 1).GetNumVertices();
        primvarRefiner.Interpolate(level, src, dst);
        src = dst;
    }
}

void interpolatePerVertex(const std::unique_ptr<OpenSubdiv::Far::TopologyRefiner> &refiner,
                          int maxlevel,
                          const OpenSubdiv::Far::PrimvarRefiner &primvarRefiner,
                          OsdVector3fAdapter *src) {
    for (int level = 1; level <= maxlevel; ++level) {
        OsdVector3fAdapter *dst = src + refiner->GetLevel(level - 1).GetNumVertices();
        primvarRefiner.InterpolateFaceVarying(level, src, dst);
        src = dst;
    }
}

OpenSubdivRefiner::OpenSubdivRefiner(SubdivisionSurfaceMesh &subdivisionSurfaceMesh) : subdivisionSurfaceMesh(
    subdivisionSurfaceMesh) {}

void OpenSubdivRefiner::refine(int maxLevel) {
    auto refiner = createRefiner();

    refiner->RefineUniform(OpenSubdiv::Far::TopologyRefiner::UniformOptions(maxLevel));

    OpenSubdiv::Far::TopologyLevel const &refLastLevel = refiner->GetLevel(maxLevel);

    refinePoints(refiner, maxLevel, refLastLevel);
    refineIndices(refLastLevel);
    refineNormals(refiner, maxLevel, refLastLevel);
}

void OpenSubdivRefiner::refinePoints(const std::unique_ptr<OpenSubdiv::Far::TopologyRefiner> &refiner,
                                     int maxlevel,
                                     const OpenSubdiv::Far::TopologyLevel &refLastLevel) {
    std::vector<Vector3f> subdividedPoints(refiner->GetNumVerticesTotal()); // todo use original points
    for (int i = 0; i < subdivisionSurfaceMesh.points.size(); i++) {
        subdividedPoints[i] = subdivisionSurfaceMesh.points[i];
    }

    OpenSubdiv::Far::PrimvarRefiner primvarRefiner(*refiner);

    auto *src = static_cast<OsdVector3fAdapter *>(subdividedPoints.data());
    interpolatePerPoint(refiner, maxlevel, primvarRefiner, src);

    subdivisionSurfaceMesh.points.resize(refLastLevel.GetNumVertices());
    int firstOfLastVerts = refiner->GetNumVerticesTotal() - refLastLevel.GetNumVertices();
    for (int i = 0; i < refLastLevel.GetNumVertices(); i++) {
        subdivisionSurfaceMesh.points[i] = subdividedPoints[firstOfLastVerts + i];
    }
}

void OpenSubdivRefiner::refineIndices(const OpenSubdiv::Far::TopologyLevel &refLastLevel) {
    std::vector<int> newFaceVertexIndices;
    const int numberOfFaces = refLastLevel.GetNumFaces();
    std::vector<int> newFaceVertexCounts;

    for (int face = 0; face < numberOfFaces; face++) {
        OpenSubdiv::Far::ConstIndexArray fverts = refLastLevel.GetFaceVertices(face);
        newFaceVertexCounts.push_back(fverts.size());
        for (int fvert: fverts) {
            newFaceVertexIndices.push_back(fvert);
        }
    }

    subdivisionSurfaceMesh.faceVertexIndices =
        newFaceVertexIndices;// TODO is this needed? Or can we just push back directly in the original vector
    subdivisionSurfaceMesh.faceVertexCounts = newFaceVertexCounts;
}

void OpenSubdivRefiner::refineNormals(const std::unique_ptr<OpenSubdiv::Far::TopologyRefiner> &refiner,
                                      int maxlevel,
                                      const OpenSubdiv::Far::TopologyLevel &refLastLevel) {
    if (!subdivisionSurfaceMesh.normalsInterpolation) {
        return;
    }

    int normalsSize = refiner->GetNumVerticesTotal();
    if (subdivisionSurfaceMesh.normalsInterpolation == PrimVarType::PER_VERTEX) {
        normalsSize = refiner->GetNumFVarValuesTotal(0);// refiner->GetLevel(maxlevel).GetNumFVarValues(0);
    }
    std::vector<Vector3f> subdividedNormals(normalsSize);
    for (int i = 0; i < subdivisionSurfaceMesh.normals.size(); i++) {
        subdividedNormals[i] = subdivisionSurfaceMesh.normals[i];
    }

    OpenSubdiv::Far::PrimvarRefiner primvarRefiner(*refiner);

    auto *src = static_cast<OsdVector3fAdapter *>(subdividedNormals.data());
    if (subdivisionSurfaceMesh.normalsInterpolation == PrimVarType::PER_POINT) {
        interpolatePerPoint(refiner, maxlevel, primvarRefiner, src);
    } else {
        interpolatePerVertex(refiner, maxlevel, primvarRefiner, src);
    }

    int normalCountForLastLevel =
        subdivisionSurfaceMesh.normalsInterpolation == PrimVarType::PER_POINT ? refLastLevel.GetNumVertices()
                                                                              : refLastLevel.GetNumFVarValues(0);
    int firstOfLastVerts = normalsSize - normalCountForLastLevel;
    if (subdivisionSurfaceMesh.normalsInterpolation == PrimVarType::PER_POINT) {
        subdivisionSurfaceMesh.normals.resize(normalCountForLastLevel);
        for (int i = 0; i < normalCountForLastLevel; i++) {
            subdivisionSurfaceMesh.normals[i] = subdividedNormals[firstOfLastVerts + i];
        }
    } else {
        const int numberOfFaces = refLastLevel.GetNumFaces();
        subdivisionSurfaceMesh.normals.clear();
        for (int face = 0; face < numberOfFaces; face++) {
            OpenSubdiv::Far::ConstIndexArray fverts = refLastLevel.GetFaceVertices(face);
            for (int fvert: fverts) {
                subdivisionSurfaceMesh.normals.push_back(subdividedNormals[firstOfLastVerts + fvert]);
            }
        }
    }
}

std::unique_ptr<OpenSubdiv::Far::TopologyRefiner> OpenSubdivRefiner::createRefiner() {
    auto descriptor = createDescriptor();

    OpenSubdiv::Sdc::SchemeType type = OpenSubdiv::Sdc::SCHEME_CATMARK;

    OpenSubdiv::Sdc::Options options;
    options.SetVtxBoundaryInterpolation(getBoundaryInterpolation());

    auto refiner =
        OpenSubdiv::v3_4_4::Far::TopologyRefinerFactory<OpenSubdiv::Far::TopologyDescriptor>::Create(descriptor,
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
    descriptor.vertIndicesPerFace =
        subdivisionSurfaceMesh.faceVertexIndices.data(); // TODO check for clockwise/counter-clockwise

    if (!subdivisionSurfaceMesh.normals.empty()) {
        channels[0].numValues = subdivisionSurfaceMesh.normals.size();
        normalsIndices.reserve(subdivisionSurfaceMesh.normals.size());
        for (int i = 0; i < subdivisionSurfaceMesh.normals.size(); i++) {
            normalsIndices.push_back(i);
        }
        channels[0].valueIndices = normalsIndices.data();

        descriptor.numFVarChannels = 1;
        descriptor.fvarChannels = channels;
    }

    return descriptor;
}

OpenSubdiv::Sdc::Options::VtxBoundaryInterpolation OpenSubdivRefiner::getBoundaryInterpolation() const {
    if (subdivisionSurfaceMesh.boundaryInterpolation == SubdivisionSurfaceMesh::BoundaryInterpolation::EDGE_ONLY) {
        return OpenSubdiv::Sdc::Options::VTX_BOUNDARY_EDGE_ONLY;
    }
    return OpenSubdiv::Sdc::Options::VTX_BOUNDARY_EDGE_AND_CORNER;
}

} // crayg