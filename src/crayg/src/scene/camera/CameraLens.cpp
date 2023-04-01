#include "CameraLens.h"
#include "Logger.h"
#include "basics/Vector2.h"

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
        lens.curvatureRadius *= 0.1;
        lens.thickness *= 0.1;
        lens.apertureRadius *= 0.1;
    }

    moveLensElements(0);
}

std::optional<Ray> CameraLens::traceRay(const Ray &ray, int startIndex, std::function<int(int)> nextLensIndex,
                                        std::function<float(int)> inIor, std::function<float(int)> outIor) const {
    Ray tracedRay = ray;
    int i = startIndex;
    while (i != -1) {
        auto lens = this->elements[i];
        if (lens.isAperture()) {
            if (lens.exceedsAperture(ray)) {
                return std::nullopt;
            }
            i = nextLensIndex(i);
            continue;
        }
        auto intersection = lens.intersect(tracedRay);
        if (!intersection) {
            return std::nullopt;
        }
        tracedRay = refract(*intersection, tracedRay, inIor(i), outIor(i));
        i = nextLensIndex(i);
    }
    return tracedRay;
}

std::optional<Ray> CameraLens::traceFromFilmToWorld(const Ray &ray) const {
    return traceRay(
        ray, elements.size() - 1, [](int i) { return i - 1; }, [this](int i) { return elements[i].ior; },
        [this](int i) { return getNextIor(i, -1); });
}

std::optional<Ray> CameraLens::traceFromWorldToFilm(const Ray &ray) const {
    return traceRay(
        ray, 0, [this](int i) { return i < elements.size() - 1 ? i + 1 : -1; },
        [this](int i) { return getNextIor(i, -1); }, [this](int i) { return elements[i].ior; });
}

Ray CameraLens::refract(const LensElementIntersection &intersection, const Ray &ray, float iorIn, float iorOut) const {
    float cosi = std::clamp(ray.direction.dot(intersection.normal), -1.0f, 1.0f);
    Vector3f n = intersection.normal;
    if (cosi < 0) {
        cosi = -cosi;
    } else {
        std::swap(iorIn, iorOut);
        n = intersection.normal.invert();
    }
    float eta = iorIn / iorOut;
    float k = 1 - eta * eta * (1 - cosi * cosi);
    Vector3f rayDirection = k < 0 ? ray.direction : (ray.direction * eta) + n * (eta * cosi - sqrtf(k));
    rayDirection = rayDirection.dot(ray.direction.invert()) < 0.f ? rayDirection : rayDirection.invert();
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

std::optional<LensElementIntersection> LensElement::intersect(const Ray &ray) {
    Vector3f D = ray.startPoint - Vector3f(0, 0, center - curvatureRadius);
    float B = D.dot(ray.direction);
    float C = D.dot(D) - curvatureRadius * curvatureRadius;
    float B2_C = B * B - C;
    if (B2_C < 0) {
        return std::nullopt;
    }
    float sgn = (curvatureRadius * ray.direction.z) > 0 ? 1 : -1;
    float t = sqrt(B2_C) * sgn - B;
    Vector3f intersectionPosition = ray.constructIntersectionPoint(t);
    Vector3f normal = intersectionPosition - Vector3f(0, 0, center - curvatureRadius).normalize();
    return LensElementIntersection(intersectionPosition, normal);
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

} // crayg