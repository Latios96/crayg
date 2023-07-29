#include "CameraLens.h"
#include "Logger.h"
#include "basics/MathUtils.h"
#include "scene/camera/CameraUtils.h"
#include <iostream>
#include <utils/Preconditions.h>

namespace crayg {

CameraLens::CameraLens(const CameraLensMetadata &metadata, const std::vector<LensElement> &elements)
    : metadata(metadata), elements(elements) {

    float center = 0;
    for (int i = elements.size() - 1; i >= 0; i--) {
        auto &lens = this->elements[i];
        center += lens.thickness;
        lens.center = center;
        if (lens.isAperture()) {
            apertureIndex = i;
        }
    }

    apertureRadius = apertureIndex != -1 ? getAperture().apertureRadius : 0;

    ThickLensApproximationCalculator thickLensCalculator(*this);
    thickLensApproximation = thickLensCalculator.calculate();

    this->metadata.focalLength = calculateEffectiveFocalLength(thickLensApproximation);
    this->metadata.elementCount = elements.size();
    if (!this->metadata.maximumAperture) {
        this->metadata.maximumAperture = this->metadata.focalLength / apertureRadius;
    }
    // todo calculate squeeze
}

CameraLens::CameraLens(const CameraLens &cameraLens)
    : metadata(cameraLens.metadata), elements(cameraLens.elements), apertureIndex(cameraLens.apertureIndex),
      thickLensApproximation(cameraLens.thickLensApproximation), apertureRadius(cameraLens.apertureRadius),
      elementsOffset(cameraLens.elementsOffset) {
}

const LensElement &CameraLens::getFirstElement() const {
    return elements[0];
}

const LensElement &CameraLens::getLastElement() const {
    return elements[elements.size() - 1];
}

std::optional<Ray> CameraLens::traceFromFilmToWorld(const Ray &ray) const {
    Ray tracedRay = {{ray.startPoint.x, ray.startPoint.y, -ray.startPoint.z},
                     {ray.direction.x, ray.direction.y, -ray.direction.z}};
    for (int i = elements.size() - 1; i >= 0; i--) {
        auto element = elements[i];
        if (element.isAperture()) {
            if (exceedsAperture(element, ray)) {
                return std::nullopt;
            }
            continue;
        }

        auto resultIntersection = intersect(element, tracedRay);
        if (!resultIntersection) {
            return std::nullopt;
        }
        float eta_i = element.ior;
        float eta_t = (i > 0 && elements[i - 1].ior != 0) ? elements[i - 1].ior : 1;

        auto result = refract(*resultIntersection, tracedRay, eta_t, eta_i);

        tracedRay = {result.startPoint, result.direction.invert()};
    }
    return Ray({tracedRay.startPoint.x, tracedRay.startPoint.y, -tracedRay.startPoint.z},
               {tracedRay.direction.x, tracedRay.direction.y, -tracedRay.direction.z});
}

std::optional<Ray> CameraLens::traceFromWorldToFilm(const Ray &ray) const {
    // todo regeneralize this
    Ray tracedRay = {{ray.startPoint.x, ray.startPoint.y, -ray.startPoint.z},
                     {ray.direction.x, ray.direction.y, -ray.direction.z}};
    for (int i = 0; i < elements.size(); i++) {
        auto element = elements[i];
        if (element.isAperture()) {
            if (exceedsAperture(element, ray)) {
                return std::nullopt;
            }
            continue;
        }

        auto resultIntersection = intersect(element, tracedRay);
        if (!resultIntersection) {
            return std::nullopt;
        }

        float eta_i = element.ior;
        float eta_t = (i > 0 && elements[i - 1].ior != 0) ? elements[i - 1].ior : 1;

        auto result = refract(*resultIntersection, tracedRay, eta_i, eta_t);

        tracedRay = {result.startPoint, result.direction.invert()};
    }
    return Ray({tracedRay.startPoint.x, tracedRay.startPoint.y, -tracedRay.startPoint.z},
               {tracedRay.direction.x, tracedRay.direction.y, -tracedRay.direction.z});
}

Ray CameraLens::refract(const LensElementIntersection &intersection, const Ray &ray, float iorIn, float iorOut) const {
    Vector3f n = intersection.normal.invert();
    float cosTheta_i = n.dot(ray.direction.normalize());
    float eta = iorIn / iorOut;
    // Potentially flip interface orientation for Snell's law
    if (cosTheta_i < 0) {
        eta = 1 / eta;
        cosTheta_i = -cosTheta_i;
        n = n.invert();
    }

    // Compute $\cos\,\theta_\roman{t}$ using Snell's law
    float sin2Theta_i = std::max<float>(0, 1 - cosTheta_i * cosTheta_i);
    float sin2Theta_t = sin2Theta_i / eta * eta;

    float cosTheta_t = std::sqrt(1 - sin2Theta_t);
    const Vector3f &f = ray.direction.invert() / eta;
    float d = cosTheta_i / eta - cosTheta_t;
    const Vector3f &f1 = n * d;
    Vector3f rayDirection = f + f1;
    return {intersection.point, rayDirection.normalize()};
}

void CameraLens::focusLens(float focalDistance) {
    const float z = -focalDistance;
    const float c =
        (thickLensApproximation.secondCardinalPoints.pZ - z - thickLensApproximation.firstCardinalPoints.pZ) *
        (thickLensApproximation.secondCardinalPoints.pZ - z - 4 * metadata.focalLength -
         thickLensApproximation.firstCardinalPoints.pZ);
    elementsOffset = 0.5f * (thickLensApproximation.secondCardinalPoints.pZ - z +
                             thickLensApproximation.firstCardinalPoints.pZ - sqrt(c));
}

LensElement &CameraLens::getAperture() {
    CRAYG_CHECK_IS_VALID_INDEX(apertureIndex, elements.size());
    return elements[apertureIndex];
}

bool CameraLens::operator==(const CameraLens &rhs) const {
    return metadata == rhs.metadata && elements == rhs.elements && apertureIndex == rhs.apertureIndex;
}

bool CameraLens::operator!=(const CameraLens &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const CameraLens &lens) {
    os << ToStringHelper("CameraLens")
              .addMember("metadata", lens.metadata)
              .addMember("elements", lens.elements)
              .finish();
    return os;
}

float CameraLens::getApertureRadius() const {
    return apertureRadius;
}

void CameraLens::changeAperture(float fStop) {
    const float requestedApertureRadius = CameraUtils::computeApertureRadius(metadata.focalLength * 10, fStop);
    const float maximumApertureRadius = getAperture().apertureRadius;
    apertureRadius = std::clamp<float>(requestedApertureRadius, 0, maximumApertureRadius);
}

inline Vector3f FaceForward(const Vector3f &n, const Vector3f &v) {
    return (n.dot(v) < 0.f) ? n.invert() : n;
}

float selectCorrectSolution(float radius, const Ray &ray, const QuadraticSolutions &quadraticSolutions) {
    auto [t0, t1] = quadraticSolutions;
    const bool isConcaveElement = radius < 0;
    const bool rayFromLeft = ray.direction.z > 0;
    bool useCloserT = rayFromLeft ^ isConcaveElement;

    if (useCloserT) {
        return std::min(t0, t1);
    }
    return std::max(t0, t1);
}

bool intersectSphericalElement(float radius, float zCenter, const Ray &ray, float *t, Vector3f *n) {
    Vector3f o = ray.startPoint - Vector3f(0, 0, zCenter);
    float A = ray.direction.dot(ray.direction);
    float B = 2 * (ray.direction.dot(o));
    float C = o.dot(o) - radius * radius;

    auto solutions = MathUtils::solveQuadratic(A, B, C);
    if (!solutions) {
        return false;
    }

    *t = selectCorrectSolution(radius, ray, *solutions);
    if (*t < 0) {
        return false;
    }

    *n = Vector3f(o + ray.direction * *t);
    *n = FaceForward(n->normalize(), ray.direction.invert());

    return true;
}

std::optional<LensElementIntersection> CameraLens::intersect(const LensElement &element, const Ray &ray) const {
    float t = 0;
    Vector3f normal;
    const bool intersects = intersectSphericalElement(
        element.curvatureRadius, -(element.center + elementsOffset) + element.curvatureRadius, ray, &t, &normal);
    if (!intersects) {
        return std::nullopt;
    }

    const Vector3f &intersectionPoint = ray.startPoint + ray.direction * t;
    if (exceedsAperture(intersectionPoint, element.apertureRadius)) {
        return std::nullopt;
    }

    return LensElementIntersection(intersectionPoint, normal);
}

bool CameraLens::exceedsAperture(const LensElement &lensElement, const Ray &ray) const {
    const float t = (lensElement.center + elementsOffset - ray.startPoint.z) / ray.direction.z;
    Vector3f intersectionPosition = ray.constructIntersectionPoint(t);
    return exceedsAperture(intersectionPosition, apertureRadius);
}

bool CameraLens::exceedsAperture(const Vector3f &intersectionPosition, float apertureRadius) const {
    const float radiusOfIntersectionSquared = intersectionPosition.xy().lengthSquared();
    const float apertureRadiusSquared = apertureRadius * apertureRadius;
    const bool rayExceedsAperture = radiusOfIntersectionSquared > apertureRadiusSquared;
    return rayExceedsAperture;
}

} // crayg