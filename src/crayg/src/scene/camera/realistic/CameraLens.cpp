#include "CameraLens.h"
#include "Logger.h"
#include "Wavelengths.h"
#include "basics/MathUtils.h"
#include "scene/camera/CameraUtils.h"
#include <iostream>
#include <utils/Preconditions.h>

namespace crayg {

CameraLens::CameraLens(const CameraLensMetadata &metadata, const std::vector<LensElement> &elements)
    : CameraLens(metadata, elements, {}) {
}

CameraLens::CameraLens(const CameraLensMetadata &metadata, const std::vector<LensElement> &elements,
                       const std::vector<AsphericCoefficients> &asphericCoefficients)
    : metadata(metadata), elements(elements), asphericCoefficients(asphericCoefficients) {

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

    initializeLensMaterials();

    ThickLensApproximationCalculator thickLensCalculator(*this);
    thickLensApproximation = thickLensCalculator.calculate(ThickLensApproximationCalculator::Direction::VERTICAL);

    calculateMetadata();

    if (this->metadata.isAnamorphic) {
        handleAnamorphicFocussing();
    }
}

void CameraLens::initializeLensMaterials() {
    for (int i = 0; i < elements.size(); i++) {
        if (i == apertureIndex) {
            continue;
        }
        auto &lensElement = elements[i];
        const bool isKnownMaterial = lensElement.material.id != LensMaterialId::UNKNOWN;
        if (isKnownMaterial) {
            lensElement.material = LensMaterial::createMaterialById(lensElement.material.id);
            continue;
        }
        if (lensElement.abbeNumber == 0) {
            lensElement.material.ior = lensElement.ior;
            continue;
        }
        LensMaterial::MaterialSearchError searchError{};
        auto material = LensMaterial::findMaterialByIorAndAbbe(lensElement.ior, lensElement.abbeNumber, &searchError);
        if (searchError.isCriticalError()) {
            Logger::error("Did not find a sufficient material for element {}, ior error: {:.3f}, abbe error: {:.3f}", i,
                          searchError.iorError, searchError.abbeNoError);
        }
        lensElement.material = material;
    }
}

void CameraLens::calculateMetadata() {
    metadata.focalLength = calculateEffectiveFocalLength(thickLensApproximation);
    metadata.elementCount = elements.size();
    if (!metadata.maximumAperture) {
        metadata.maximumAperture = metadata.focalLength / apertureRadius;
    }
    metadata.isAnamorphic = std::any_of(elements.begin(), elements.end(), [](const LensElement &element) {
        return element.geometry == LensGeometry::CYLINDER_X || element.geometry == LensGeometry::CYLINDER_Y;
    });
    metadata.closestFocalDistance = computeClosestFocalDistance();
}

void CameraLens::handleAnamorphicFocussing() {
    ThickLensApproximationCalculator thickLensCalculator(*this);
    auto horizontalThickLensApproximation =
        thickLensCalculator.calculate(ThickLensApproximationCalculator::Direction::HORIZONTAL);
    auto horizontalFocalLength = calculateEffectiveFocalLength(horizontalThickLensApproximation);
    metadata.squeeze = metadata.focalLength / horizontalFocalLength;
    metadata.focalLength = horizontalFocalLength;
    thickLensApproximation = horizontalThickLensApproximation;
}

float CameraLens::calculateElementsOffset(float focalDistance) const {
    const float z = -focalDistance;
    const float c =
        (thickLensApproximation.secondCardinalPoints.pZ - z - thickLensApproximation.firstCardinalPoints.pZ) *
        (thickLensApproximation.secondCardinalPoints.pZ - z - 4 * metadata.focalLength -
         thickLensApproximation.firstCardinalPoints.pZ);
    return 0.5f * (thickLensApproximation.secondCardinalPoints.pZ - z + thickLensApproximation.firstCardinalPoints.pZ -
                   sqrt(c));
}

float CameraLens::computeClosestFocalDistance() const {
    float middle = 0;
    float start = 250;
    float end = 0;
    for (int i = 0; i < 10; i++) {
        middle = end + ((start - end) / 2.f);
        const float offset = calculateElementsOffset(middle);
        if (std::isnan(offset)) {
            end = middle;
        } else {
            start = middle;
        }
    }
    return middle;
}

CameraLens::CameraLens(const CameraLens &cameraLens)
    : metadata(cameraLens.metadata), elements(cameraLens.elements),
      asphericCoefficients(cameraLens.asphericCoefficients), apertureIndex(cameraLens.apertureIndex),
      thickLensApproximation(cameraLens.thickLensApproximation), apertureRadius(cameraLens.apertureRadius),
      elementsOffset(cameraLens.elementsOffset) {
}

const LensElement &CameraLens::getFirstElement() const {
    return elements[0];
}

const LensElement &CameraLens::getLastElement() const {
    return elements[elements.size() - 1];
}

std::optional<Ray> CameraLens::traceFromFilmToWorld(const Ray &ray, float wavelength) const {
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
        float eta_i = element.material.getIor(wavelength);
        float eta_t = (i > 0 && elements[i - 1].material.getIor(wavelength) != 0)
                          ? elements[i - 1].material.getIor(wavelength)
                          : 1;

        auto result = refract(*resultIntersection, tracedRay, eta_t, eta_i);

        tracedRay = {result.startPoint, result.direction.invert()};
    }
    return Ray({tracedRay.startPoint.x, tracedRay.startPoint.y, -tracedRay.startPoint.z},
               {tracedRay.direction.x, tracedRay.direction.y, -tracedRay.direction.z});
}

std::optional<Ray> CameraLens::traceFromWorldToFilm(const Ray &ray, float wavelength) const {
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

        float eta_i = element.material.getIor(wavelength);
        float eta_t = (i > 0 && elements[i - 1].material.getIor(wavelength) != 0)
                          ? elements[i - 1].material.getIor(wavelength)
                          : 1;

        auto result = refract(*resultIntersection, tracedRay, eta_i, eta_t);

        tracedRay = {result.startPoint, result.direction.invert()};
    }
    return Ray({tracedRay.startPoint.x, tracedRay.startPoint.y, -tracedRay.startPoint.z},
               {tracedRay.direction.x, tracedRay.direction.y, -tracedRay.direction.z});
}

std::vector<Vector3f> CameraLens::traceAndRecordFromWorldToFilm(const Ray &ray, float wavelength) const {
    std::vector<Vector3f> recordedPoints;
    recordedPoints.reserve(elements.size() + 2);

    Ray tracedRay = {{ray.startPoint.x, ray.startPoint.y, -ray.startPoint.z},
                     {ray.direction.x, ray.direction.y, -ray.direction.z}};

    recordedPoints.push_back(tracedRay.startPoint);

    for (int i = 0; i < elements.size(); i++) {
        auto element = elements[i];
        if (element.isAperture()) {
            if (exceedsAperture(element, ray)) {
                return recordedPoints;
            }
            continue;
        }

        auto resultIntersection = intersect(element, tracedRay);
        if (!resultIntersection) {
            return recordedPoints;
        }

        float eta_i = element.material.getIor(wavelength);
        float eta_t = (i > 0 && elements[i - 1].material.getIor(wavelength) != 0)
                          ? elements[i - 1].material.getIor(wavelength)
                          : 1;

        auto result = refract(*resultIntersection, tracedRay, eta_i, eta_t);

        tracedRay = {result.startPoint, result.direction.invert()};
        recordedPoints.push_back(tracedRay.startPoint);
    }

    Vector3f pointOnFilm =
        tracedRay.startPoint - (tracedRay.direction / tracedRay.direction.z) * tracedRay.startPoint.z;
    recordedPoints.push_back(pointOnFilm);

    return recordedPoints;
}

Ray CameraLens::refract(const LensElementIntersection &intersection, const Ray &ray, float iorIn, float iorOut) const {
    Vector3f n = intersection.normal.invert();
    float cosTheta_i = n.dot(ray.direction);
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
    if (focalDistance < metadata.closestFocalDistance) {
        Logger::warning("Focal distance {} is shorter than closest focal distance, clamping to {}", focalDistance,
                        metadata.closestFocalDistance);
        focalDistance = metadata.closestFocalDistance;
    }
    elementsOffset = calculateElementsOffset(focalDistance);
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
              .addMember("asphericCoefficients", lens.asphericCoefficients)
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

std::optional<LensElementIntersection> CameraLens::intersect(const LensElement &element, const Ray &ray) const {
    float t = 0;
    Vector3f normal;
    bool intersects = false;

    switch (element.geometry) {
    case LensGeometry::SPHERICAL:
        intersects = intersectSphericalElement(
            element.curvatureRadius, -(element.center + elementsOffset) + element.curvatureRadius, ray, &t, &normal);
        break;
    case LensGeometry::ASPHERICAL:
        intersects = intersectAsphericalElement(element.curvatureRadius,
                                                -(element.center + elementsOffset) + element.curvatureRadius, ray, &t,
                                                &normal, asphericCoefficients[*element.asphericCoefficientsIndex]);
        break;
    case LensGeometry::CYLINDER_X:
        intersects = intersectCylindricalXElement(
            element.curvatureRadius, -(element.center + elementsOffset) + element.curvatureRadius, ray, &t, &normal);
        break;
    case LensGeometry::CYLINDER_Y:
        intersects = intersectCylindricalYElement(
            element.curvatureRadius, -(element.center + elementsOffset) + element.curvatureRadius, ray, &t, &normal);
        break;
    case LensGeometry::PLANAR:
        intersects =
            intersectPlanarElement(-(element.center + elementsOffset) + element.curvatureRadius, ray, &t, &normal);
        break;
    }

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

bool CameraLens::hasAsphericElements() const {
    return !asphericCoefficients.empty();
}

float CameraLens::length() const {
    float length = 0;
    for (auto &element : elements) {
        length += element.thickness;
    }
    return length;
}

} // crayg