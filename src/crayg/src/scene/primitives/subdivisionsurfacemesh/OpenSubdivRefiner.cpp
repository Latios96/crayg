#include "OpenSubdivRefiner.h"
#include <opensubdiv/far/primvarRefiner.h>
#include <opensubdiv/far/topologyRefinerFactory.h>

namespace crayg {

class OsdVector3fAdapter : public Vector3f {
  public:
    OsdVector3fAdapter() : Vector3f() {
    }

    OsdVector3fAdapter(const Vector3f &src) : Vector3f(src) {
    }

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

class OsdVector2fAdapter : public Vector2f {
  public:
    OsdVector2fAdapter() : Vector2f() {
    }

    OsdVector2fAdapter(const Vector2f &src) : Vector2f(src) {
    }

    void Clear(void * = 0) {
        x = 0;
        y = 0;
    }

    void AddWithWeight(OsdVector2fAdapter const &src, float weight) {
        x += weight * src.x;
        y += weight * src.y;
    }
};

OpenSubdivRefiner::OpenSubdivRefiner(SubdivisionSurfaceMesh &subdivisionSurfaceMesh)
    : subdivisionSurfaceMesh(subdivisionSurfaceMesh) {
}

void OpenSubdivRefiner::refine(int maxLevel) {
    if (subdivisionSurfaceMesh.points.empty()) {
        return;
    }
    auto refiner = createRefiner();

    auto uniformOptions = OpenSubdiv::Far::TopologyRefiner::UniformOptions(maxLevel);
    uniformOptions.fullTopologyInLastLevel = true;
    refiner->RefineUniform(uniformOptions);

    OpenSubdiv::Far::TopologyLevel const &refLastLevel = refiner->GetLevel(maxLevel);

    refinePoints(refiner, maxLevel, refLastLevel);
    refineIndices(refLastLevel);
    refineNormals(refiner, refLastLevel);
    refineUvs(refiner, maxLevel, refLastLevel);
}

void OpenSubdivRefiner::refinePoints(const std::unique_ptr<OpenSubdiv::Far::TopologyRefiner> &refiner, int maxlevel,
                                     const OpenSubdiv::Far::TopologyLevel &refLastLevel) {
    std::vector<Vector3f> subdividedPoints(refiner->GetNumVerticesTotal());
    for (int i = 0; i < subdivisionSurfaceMesh.points.size(); i++) {
        subdividedPoints[i] = subdivisionSurfaceMesh.points[i];
    }

    OpenSubdiv::Far::PrimvarRefiner primvarRefiner(*refiner);

    auto *src = static_cast<OsdVector3fAdapter *>(subdividedPoints.data());
    OsdVector3fAdapter *src1 = src;
    for (int level = 1; level <= maxlevel; ++level) {
        OsdVector3fAdapter *dst = src1 + refiner->GetLevel(level - 1).GetNumVertices();
        primvarRefiner.Interpolate(level, src1, dst);
        src1 = dst;
    }

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
        for (int fvert : fverts) {
            newFaceVertexIndices.push_back(fvert);
        }
    }

    subdivisionSurfaceMesh.faceVertexIndices = newFaceVertexIndices;
    subdivisionSurfaceMesh.faceVertexCounts = newFaceVertexCounts;
}

void OpenSubdivRefiner::refineNormals(const std::unique_ptr<OpenSubdiv::Far::TopologyRefiner> &refiner,
                                      const OpenSubdiv::Far::TopologyLevel &refLastLevel) {
    int numberOfVertices = refLastLevel.GetNumVertices();
    int firstOfLastVerts = refiner->GetNumVerticesTotal() - numberOfVertices;
    std::vector<Vector3f> fineLimitPos(numberOfVertices);
    std::vector<Vector3f> fineDu(numberOfVertices);
    std::vector<Vector3f> fineDv(numberOfVertices);
    subdivisionSurfaceMesh.normals.resize(numberOfVertices);

    OpenSubdiv::Far::PrimvarRefiner primvarRefiner(*refiner);

    auto *src = static_cast<OsdVector3fAdapter *>(subdivisionSurfaceMesh.points.data());
    auto *fineLimitPosAdapter = static_cast<OsdVector3fAdapter *>(fineLimitPos.data());
    auto *fineDuAdapter = static_cast<OsdVector3fAdapter *>(fineDu.data());
    auto *fineDvAdapter = static_cast<OsdVector3fAdapter *>(fineDv.data());
    primvarRefiner.Limit(src, fineLimitPosAdapter, fineDuAdapter, fineDvAdapter);

    for (int vert = 0; vert < numberOfVertices; ++vert) {
        const auto &du = fineDu[vert];
        const auto &dv = fineDv[vert];
        subdivisionSurfaceMesh.normals[vert] = du.cross(dv);
    }
}

std::unique_ptr<OpenSubdiv::Far::TopologyRefiner> OpenSubdivRefiner::createRefiner() {
    auto descriptor = createDescriptor();

    OpenSubdiv::Sdc::SchemeType type = OpenSubdiv::Sdc::SCHEME_CATMARK;

    OpenSubdiv::Sdc::Options options;
    options.SetVtxBoundaryInterpolation(getBoundaryInterpolation());

    auto refiner = OpenSubdiv::Far::TopologyRefinerFactory<OpenSubdiv::Far::TopologyDescriptor>::Create(
        descriptor,
        OpenSubdiv::Far::TopologyRefinerFactory<OpenSubdiv::Far::TopologyDescriptor>::Options(type, options));
    return std::unique_ptr<OpenSubdiv::Far::TopologyRefiner>(refiner);
}

OpenSubdiv::Far::TopologyDescriptor OpenSubdivRefiner::createDescriptor() {
    OpenSubdiv::Far::TopologyDescriptor descriptor;
    descriptor.numVertices = subdivisionSurfaceMesh.points.size();
    descriptor.numFaces = subdivisionSurfaceMesh.faceCount();
    descriptor.numVertsPerFace = subdivisionSurfaceMesh.faceVertexCounts.data();
    descriptor.vertIndicesPerFace = subdivisionSurfaceMesh.faceVertexIndices.data();

    if (!subdivisionSurfaceMesh.uvs.empty() && !subdivisionSurfaceMesh.uvIndices.empty()) {
        channels[0].numValues = subdivisionSurfaceMesh.uvs.size();
        channels[0].valueIndices = subdivisionSurfaceMesh.uvIndices.data();
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

void OpenSubdivRefiner::refineUvs(const std::unique_ptr<OpenSubdiv::Far::TopologyRefiner> &refiner, int maxlevel,
                                  const OpenSubdiv::Far::TopologyLevel &refLastLevel) {
    if (subdivisionSurfaceMesh.uvs.empty() || subdivisionSurfaceMesh.uvIndices.empty()) {
        return;
    }
    std::vector<Vector2f> subdividedUvs(refiner->GetNumFVarValuesTotal(0));
    for (int i = 0; i < subdivisionSurfaceMesh.uvs.size(); i++) {
        subdividedUvs[i] = subdivisionSurfaceMesh.uvs[i];
    }

    OpenSubdiv::Far::PrimvarRefiner primvarRefiner(*refiner);

    auto *src = static_cast<OsdVector2fAdapter *>(subdividedUvs.data());
    OsdVector2fAdapter *src1 = src;
    for (int level = 1; level <= maxlevel; ++level) {
        OsdVector2fAdapter *dst = src1 + refiner->GetLevel(level - 1).GetNumFVarValues();
        primvarRefiner.InterpolateFaceVarying(level, src1, dst);
        src1 = dst;
    }

    subdivisionSurfaceMesh.uvs.resize(refLastLevel.GetNumFVarValues());
    int firstOfLastUvs = refiner->GetNumFVarValuesTotal() - refLastLevel.GetNumFVarValues();
    for (int i = 0; i < refLastLevel.GetNumFVarValues(); i++) {
        subdivisionSurfaceMesh.uvs[i] = subdividedUvs[firstOfLastUvs + i];
    }

    std::vector<int> newUvIndices;
    const int numberOfFaces = refLastLevel.GetNumFaces();

    for (int face = 0; face < numberOfFaces; face++) {
        OpenSubdiv::Far::ConstIndexArray fverts = refLastLevel.GetFaceFVarValues(face);
        for (int fvert : fverts) {
            newUvIndices.push_back(fvert);
        }
    }

    subdivisionSurfaceMesh.uvIndices = newUvIndices;
}

} // crayg