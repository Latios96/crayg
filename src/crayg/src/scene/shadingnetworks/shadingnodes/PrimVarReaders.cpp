#include "PrimVarReaders.h"
#include "scene/primitives/Sphere.h"
#include "scene/primitives/trianglemesh/Triangle.h"
#include "scene/primitives/trianglemesh/TriangleMesh.h"
#include <boost/math/constants/constants.hpp>

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
        if (!triangle->triangleMesh->uvsPrimVar) {
            return Vector2f();
        }
        return triangle->triangleMesh->uvsPrimVar->interpolateAt(triangle->faceId, surfaceInteraction.point);
    }
    if (surfaceInteraction.imageable.imageableType == ImageableType::SPHERE) {
        Sphere *sphere = (Sphere *)&surfaceInteraction.imageable;
        const Vector3f pointInOrigin =
            sphere->getTransform().applyInverseForPoint(surfaceInteraction.point) / sphere->getRadius();

        const float u = 0.5f + std::atan2(pointInOrigin.y, pointInOrigin.x) / 2 * boost::math::constants::pi<float>();
        const float v = 0.5f + std::asin(pointInOrigin.z) / boost::math::constants::pi<float>();

        return {u, v};
    }
    return {};
}

std::string PrimVarReaderVector2f::getType() const {
    return "PrimVarReaderVector2f";
}

ShadingNodeOutputType PrimVarReaderVector2f::getOutputType() {
    return ShadingNodeOutputType::VECTOR2F;
}

}