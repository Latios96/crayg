#include "PrimVarReaders.h"
#include "scene/primitives/trianglemesh/Triangle.h"
#include "scene/primitives/trianglemesh/TriangleMesh.h"

namespace crayg {

Vector2f PrimVarReaderVector2f::evaluateVector2f(const SurfaceInteraction &surfaceInteraction) {
    if (primVarReaderType == PrimVarReaderType::UNKNOWN) {
        return {};
    }
    if (primVarReaderType == PrimVarReaderType::UV) {
        return readUvs(surfaceInteraction);
    }

    return {};
}

Vector2f PrimVarReaderVector2f::readUvs(const SurfaceInteraction &surfaceInteraction) {
    if (surfaceInteraction.imageable.imageableType == ImageableType::TRIANGLE) {
        Triangle *triangle = (Triangle *)&surfaceInteraction.imageable;
        return triangle->triangleMesh->uvsPrimVar->interpolateAt(triangle->faceId, surfaceInteraction.point);
    }
    return {};
}

std::string PrimVarReaderVector2f::getType() const {
    return "PrimVarReaderVector2f";
}

ShadingNodeOutputType PrimVarReaderVector2f::getOutputType() {
    return ShadingNodeOutputType::VECTOR2F;
}

} // crayg