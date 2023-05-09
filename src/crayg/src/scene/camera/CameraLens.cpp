#include "CameraLens.h"
#include "Logger.h"
#include "ThickLensApproximation.h"
#include "basics/MathUtils.h"
#include <iostream>
#include <utils/Preconditions.h>

namespace crayg {

LensElement::LensElement(float curvatureRadius, float thickness, float ior, float apertureRadius)
    : curvatureRadius(curvatureRadius), thickness(thickness), ior(ior), apertureRadius(apertureRadius), center(0) {
}

bool LensElement::isAperture() const {
    return curvatureRadius == 0;
}

const LensElement &CameraLens::getFirstElement() const {
    return elements[0];
}

const LensElement &CameraLens::getLastElement() const {
    return elements[elements.size() - 1];
}

CameraLens::CameraLens(const std::string &name, const std::vector<LensElement> &elements)
    : name(name), elements(elements) {

    for (int i = elements.size() - 1; i >= 0; i--) {
        auto &lens = this->elements[i];
        if (lens.isAperture()) {
            apertureIndex = i;
        }
    }

    moveLensElements(0);
}

CameraLens::CameraLens(const CameraLens &cameraLens)
    : name(cameraLens.name), elements(cameraLens.elements), apertureIndex(cameraLens.apertureIndex) {
}

std::optional<Ray> CameraLens::traceFromFilmToWorld(const Ray &ray) const {
    Ray tracedRay = {{ray.startPoint.x, ray.startPoint.y, -ray.startPoint.z},
                     {ray.direction.x, ray.direction.y, -ray.direction.z}};
    for (int i = elements.size() - 1; i >= 0; i--) {
        auto element = elements[i];
        if (element.isAperture()) {
            if (element.exceedsAperture(ray)) {
                return std::nullopt;
            }
            continue;
        }

        auto resultIntersection = element.intersect(tracedRay);
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
            if (element.exceedsAperture(ray)) {
                return std::nullopt;
            }
            continue;
        }

        auto resultIntersection = element.intersect(tracedRay);
        if (!resultIntersection) {
            return std::nullopt;
        }

        float eta_i = element.ior;
        float eta_t = (i > 0 && elements[i - 1].ior != 0) ? elements[i - 1].ior : 1;

        auto result = refract(*resultIntersection, tracedRay, /*getNextIor(i,-1),element.ior*/ eta_i, eta_t);

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

float CameraLens::getNextIor(int currentIndex, int indexOffset) const {
    if (currentIndex == 0) {
        return 1;
    }
    const auto nextLens = elements[currentIndex + indexOffset];
    if (nextLens.isAperture()) {
        return 1;
    }
    return nextLens.ior;
}

void CameraLens::moveLensElements(float offset) {
    float center = offset;
    for (int i = elements.size() - 1; i >= 0; i--) {
        auto &lens = this->elements[i];
        center += lens.thickness;
        lens.center = center;
    }
}

void CameraLens::focusLens(float focalDistance) {
    ThickLensApproximationCalculator thickLensCalculator(*this);
    auto thickLens = thickLensCalculator.calculate();

    const float focalLength = calculateEffectiveFocalLength(thickLens);
    Logger::info("Effective focal length: {:.2f}mm", focalLength * 10);

    const float z = -focalDistance;
    const float c = (thickLens.secondCardinalPoints.pZ - z - thickLens.firstCardinalPoints.pZ) *
                    (thickLens.secondCardinalPoints.pZ - z - 4 * focalLength - thickLens.firstCardinalPoints.pZ);
    const float delta = 0.5f * (thickLens.secondCardinalPoints.pZ - z + thickLens.firstCardinalPoints.pZ - sqrt(c));

    moveLensElements(delta);
}

LensElement &CameraLens::getAperture() {
    CRAYG_CHECK_IS_VALID_INDEX(apertureIndex, elements.size());
    return elements[apertureIndex];
}

bool CameraLens::operator==(const CameraLens &rhs) const {
    return name == rhs.name && elements == rhs.elements && apertureIndex == rhs.apertureIndex;
}

bool CameraLens::operator!=(const CameraLens &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const CameraLens &lens) {
    os << ToStringHelper("CameraLens").addMember("name", lens.name).addMember("elements", lens.elements).finish();
    return os;
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

bool IntersectSphericalElement(float radius, float zCenter, const Ray &ray, float *t, Vector3f *n) {
    Vector3f o = ray.startPoint - Vector3f(0, 0, zCenter);
    float A = ray.direction.x * ray.direction.x + ray.direction.y * ray.direction.y + ray.direction.z * ray.direction.z;
    float B = 2 * (ray.direction.x * o.x + ray.direction.y * o.y + ray.direction.z * o.z);
    float C = o.x * o.x + o.y * o.y + o.z * o.z - radius * radius;

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

std::optional<LensElementIntersection> LensElement::intersect(const Ray &ray) {
    float t = 0;
    Vector3f normal;
    const bool intersects = IntersectSphericalElement(curvatureRadius, -center + curvatureRadius, ray, &t, &normal);
    if (!intersects) {
        return std::nullopt;
    }

    const Vector3f &intersectionPoint = ray.startPoint + ray.direction * t;
    if (exceedsAperture(intersectionPoint)) {
        return std::nullopt;
    }

    return LensElementIntersection(intersectionPoint, normal);
}

bool LensElement::exceedsAperture(const Ray &ray) const {
    const float t = (center - ray.startPoint.z) / ray.direction.z;
    Vector3f intersectionPosition = ray.constructIntersectionPoint(t); // todo respect aperture opening here
    return exceedsAperture(intersectionPosition);
}

bool LensElement::exceedsAperture(const Vector3f &intersectionPosition) const {
    const float radiusOfIntersectionSquared = intersectionPosition.xy().lengthSquared();
    const float apertureRadiusSquared = std::pow(apertureRadius, 2.f);
    const bool rayExceedsAperture = radiusOfIntersectionSquared > apertureRadiusSquared;
    return rayExceedsAperture;
}

bool LensElement::operator==(const LensElement &rhs) const {
    return curvatureRadius == rhs.curvatureRadius && thickness == rhs.thickness && ior == rhs.ior &&
           apertureRadius == rhs.apertureRadius && center == rhs.center;
}

bool LensElement::operator!=(const LensElement &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const LensElement &element) {
    os << ToStringHelper("LensElement")
              .addMember("curvatureRadius", element.curvatureRadius)
              .addMember("thickness", element.thickness)
              .addMember("ior", element.ior)
              .addMember("apertureRadius", element.apertureRadius)
              .addMember("center", element.center)
              .finish();
    return os;
}

} // crayg