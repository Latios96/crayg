#include "CameraLens.h"
#include "Logger.h"

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
    float center = 0;
    for (int i = elements.size() - 1; i >= 0; i--) {
        auto &lens = this->elements[i];
        lens.curvatureRadius *= 0.1;
        lens.thickness *= 0.1;
        lens.apertureRadius *= 0.1;
        center += lens.thickness;
        lens.center = center;
    }
}

Ray CameraLens::traceFromFilmToWorld(const Ray &ray) const {
    Ray tracedRay = ray;
    for (int i = elements.size() - 1; i >= 0; i--) {
        auto lens = elements[i];
        if (lens.isAperture()) {
            continue;
        }
        auto intersection = lens.intersect(tracedRay);
        tracedRay = refract(*intersection, tracedRay, lens.ior, getNextIor(i, -1));
    }
    return tracedRay;
}

Ray CameraLens::traceFromWorldToFilm(const Ray &ray) const {
    Ray tracedRay = ray;
    for (int i = 0; i < elements.size(); i++) {
        auto lens = elements[i];
        if (lens.isAperture()) {
            continue;
        }
        auto intersection = lens.intersect(tracedRay);
        tracedRay = refract(*intersection, tracedRay, getNextIor(i, -1), lens.ior);
    }
    return tracedRay;
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

} // crayg