#include "CameraLens.h"
#include "Logger.h"
#include "Wavelengths.h"
#include "basics/MathUtils.h"
#include "scene/camera/CameraUtils.h"
#include <iostream>
#include <utils/Preconditions.h>

namespace crayg {

CameraLens::CameraLens(const CameraLensMetadata &metadata, const std::vector<LensSurface> &surfaces)
    : CameraLens(metadata, surfaces, {}, {}) {
}

CameraLens::CameraLens(const CameraLensMetadata &metadata, const std::vector<LensSurface> &surfaces,
                       const std::vector<AsphericCoefficients> &asphericCoefficients,
                       const VariableLensDistances &variableLensDistances)
    : metadata(metadata), surfaces(surfaces), asphericCoefficients(asphericCoefficients),
      variableLensDistances(variableLensDistances) {

    initSurfaceCenters();
    // todo extract method
    for (int i = surfaces.size() - 1; i >= 0; i--) {
        auto &surface = this->surfaces[i];
        if (surface.isAperture()) {
            apertureIndex = i;
        }
    }
    apertureRadius = apertureIndex != -1 ? getAperture().apertureRadius : 0;

    initializeLensMaterials();
    initializeLensProperties();
}

void CameraLens::initializeLensMaterials() {
    for (int i = 0; i < surfaces.size(); i++) {
        if (i == apertureIndex) {
            continue;
        }
        auto &surface = surfaces[i];
        const bool isKnownMaterial = surface.material.id != LensMaterialId::UNKNOWN;
        if (isKnownMaterial) {
            surface.material = LensMaterial::createMaterialById(surface.material.id);
            continue;
        }
        if (surface.abbeNumber == 0) {
            surface.material.ior = surface.ior;
            continue;
        }
        LensMaterial::MaterialSearchError searchError{};
        auto material = LensMaterial::findMaterialByIorAndAbbe(surface.ior, surface.abbeNumber, &searchError);
        if (searchError.isCriticalError()) {
            Logger::error("Did not find a sufficient material for surface {}, ior error: {:.3f}, abbe error: {:.3f}", i,
                          searchError.iorError, searchError.abbeNoError);
        }
        surface.material = material;
    }
}

void CameraLens::initSurfaceCenters() {
    float center = surfacesOffset;
    for (int i = surfaces.size() - 1; i >= 0; i--) {
        auto &surface = this->surfaces[i];
        center += surface.thickness;
        surface.center = center;
    }
}

void CameraLens::initializeLensProperties() {
    ThickLensApproximationCalculator thickLensCalculator(*this);
    thickLensApproximation = thickLensCalculator.calculate(ThickLensApproximationCalculator::Direction::VERTICAL);

    calculateMetadata();

    if (this->metadata.isAnamorphic) {
        handleAnamorphicFocussing();
    }
}

void CameraLens::calculateMetadata() {
    metadata.focalLength = calculateEffectiveFocalLength(thickLensApproximation);
    metadata.surfaceCount = surfaces.size();
    if (!metadata.maximumAperture) {
        metadata.maximumAperture = metadata.focalLength / apertureRadius;
    }
    metadata.isAnamorphic = std::any_of(surfaces.begin(), surfaces.end(), [](const LensSurface &surface) {
        return surface.geometry == LensGeometry::CYLINDER_X || surface.geometry == LensGeometry::CYLINDER_Y;
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

float CameraLens::calculateSurfaceOffset(float focalDistance) const {
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
        const float offset = calculateSurfaceOffset(middle);
        if (std::isnan(offset)) {
            end = middle;
        } else {
            start = middle;
        }
    }
    return middle;
}

CameraLens::CameraLens(const CameraLens &cameraLens)
    : metadata(cameraLens.metadata), surfaces(cameraLens.surfaces),
      asphericCoefficients(cameraLens.asphericCoefficients), apertureIndex(cameraLens.apertureIndex),
      thickLensApproximation(cameraLens.thickLensApproximation), apertureRadius(cameraLens.apertureRadius),
      surfacesOffset(cameraLens.surfacesOffset), variableLensDistances(cameraLens.variableLensDistances) {
    initSurfaceCenters();
}

const LensSurface &CameraLens::getFirstSurface() const {
    return surfaces[0];
}

const LensSurface &CameraLens::getLastSurface() const {
    return surfaces[surfaces.size() - 1];
}

std::optional<Ray> CameraLens::traceFromFilmToWorld(const Ray &ray, float wavelength) const {
    Ray tracedRay = {{ray.startPoint.x, ray.startPoint.y, -ray.startPoint.z},
                     {ray.direction.x, ray.direction.y, -ray.direction.z}};
    for (int i = surfaces.size() - 1; i >= 0; i--) {
        auto surface = surfaces[i];
        if (surface.isAperture()) {
            if (exceedsAperture(surface, ray)) {
                return std::nullopt;
            }
            continue;
        }

        auto resultIntersection = intersect(surface, tracedRay);
        if (!resultIntersection) {
            return std::nullopt;
        }
        float eta_i = surface.material.getIor(wavelength);
        float eta_t = (i > 0 && surfaces[i - 1].material.getIor(wavelength) != 0)
                          ? surfaces[i - 1].material.getIor(wavelength)
                          : 1;

        auto result = refract(*resultIntersection, tracedRay, eta_t, eta_i);

        tracedRay = {result.startPoint, result.direction.invert()};
    }
    return Ray({tracedRay.startPoint.x, tracedRay.startPoint.y, -tracedRay.startPoint.z},
               {tracedRay.direction.x, tracedRay.direction.y, -tracedRay.direction.z});
}

std::optional<Ray> CameraLens::traceFromFilmToWorld(const Ray &ray, float wavelength,
                                                    float *maxRelativeDistanceToOpticalAxis) const {
    Ray tracedRay = {{ray.startPoint.x, ray.startPoint.y, -ray.startPoint.z},
                     {ray.direction.x, ray.direction.y, -ray.direction.z}};
    for (int i = surfaces.size() - 1; i >= 0; i--) {
        auto surface = surfaces[i];
        if (surface.isAperture()) {
            if (exceedsAperture(surface, ray)) {
                const float t = (getSurfaceCenter(surface) - ray.startPoint.z) / ray.direction.z;
                Vector3f intersectionPosition = ray.constructIntersectionPoint(t);
                const float relativeDistanceToOpticalAxis = intersectionPosition.xy().length() / surface.apertureRadius;
                *maxRelativeDistanceToOpticalAxis =
                    std::max(*maxRelativeDistanceToOpticalAxis, relativeDistanceToOpticalAxis);
            }
            continue;
        }

        auto resultIntersection = intersect(surface, tracedRay);
        if (!resultIntersection) {
            *maxRelativeDistanceToOpticalAxis = 1;
        }
        float eta_i = surface.material.getIor(wavelength);
        float eta_t = (i > 0 && surfaces[i - 1].material.getIor(wavelength) != 0)
                          ? surfaces[i - 1].material.getIor(wavelength)
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
    for (int i = 0; i < surfaces.size(); i++) {
        auto surface = surfaces[i];
        if (surface.isAperture()) {
            if (exceedsAperture(surface, ray)) {
                return std::nullopt;
            }
            continue;
        }

        auto resultIntersection = intersect(surface, tracedRay);
        if (!resultIntersection) {
            return std::nullopt;
        }

        float eta_i = surface.material.getIor(wavelength);
        float eta_t = (i > 0 && surfaces[i - 1].material.getIor(wavelength) != 0)
                          ? surfaces[i - 1].material.getIor(wavelength)
                          : 1;

        auto result = refract(*resultIntersection, tracedRay, eta_i, eta_t);

        tracedRay = {result.startPoint, result.direction.invert()};
    }
    return Ray({tracedRay.startPoint.x, tracedRay.startPoint.y, -tracedRay.startPoint.z},
               {tracedRay.direction.x, tracedRay.direction.y, -tracedRay.direction.z});
}

std::vector<Vector3f> CameraLens::traceAndRecordFromWorldToFilm(const Ray &ray, float wavelength) const {
    std::vector<Vector3f> recordedPoints;
    recordedPoints.reserve(surfaces.size() + 2);

    Ray tracedRay = {{ray.startPoint.x, ray.startPoint.y, -ray.startPoint.z},
                     {ray.direction.x, ray.direction.y, -ray.direction.z}};

    recordedPoints.push_back(tracedRay.startPoint);

    for (int i = 0; i < surfaces.size(); i++) {
        auto surface = surfaces[i];
        if (surface.isAperture()) {
            if (exceedsAperture(surface, ray)) {
                return recordedPoints;
            }
            continue;
        }

        auto resultIntersection = intersect(surface, tracedRay);
        if (!resultIntersection) {
            return recordedPoints;
        }

        float eta_i = surface.material.getIor(wavelength);
        float eta_t = (i > 0 && surfaces[i - 1].material.getIor(wavelength) != 0)
                          ? surfaces[i - 1].material.getIor(wavelength)
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

Ray CameraLens::refract(const LensSurfaceIntersection &intersection, const Ray &ray, float iorIn, float iorOut) const {
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
    surfacesOffset = calculateSurfaceOffset(focalDistance);
}

LensSurface &CameraLens::getAperture() {
    CRAYG_CHECK_IS_VALID_INDEX(apertureIndex, surfaces.size());
    return surfaces[apertureIndex];
}

bool CameraLens::operator==(const CameraLens &rhs) const {
    return metadata == rhs.metadata && surfaces == rhs.surfaces && apertureIndex == rhs.apertureIndex;
}

bool CameraLens::operator!=(const CameraLens &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const CameraLens &lens) {
    os << ToStringHelper("CameraLens")
              .addMember("metadata", lens.metadata)
              .addMember("surfaces", lens.surfaces)
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

std::optional<LensSurfaceIntersection> CameraLens::intersect(const LensSurface &surface, const Ray &ray) const {
    float t = 0;
    Vector3f normal;
    bool intersects = false;

    switch (surface.geometry) {
    case LensGeometry::SPHERICAL:
        intersects = intersectSphericalSurface(
            surface.curvatureRadius, -(getSurfaceCenter(surface)) + surface.curvatureRadius, ray, &t, &normal);
        break;
    case LensGeometry::ASPHERICAL:
        intersects =
            intersectAsphericalSurface(surface.curvatureRadius, -(getSurfaceCenter(surface)) + surface.curvatureRadius,
                                       ray, &t, &normal, asphericCoefficients[*surface.asphericCoefficientsIndex]);
        break;
    case LensGeometry::CYLINDER_X:
        intersects = intersectCylindricalXSurface(
            surface.curvatureRadius, -(getSurfaceCenter(surface)) + surface.curvatureRadius, ray, &t, &normal);
        break;
    case LensGeometry::CYLINDER_Y:
        intersects = intersectCylindricalYSurface(
            surface.curvatureRadius, -(getSurfaceCenter(surface)) + surface.curvatureRadius, ray, &t, &normal);
        break;
    case LensGeometry::PLANAR:
        intersects = intersectPlanarSurface(-(getSurfaceCenter(surface)) + surface.curvatureRadius, ray, &t, &normal);
        break;
    }

    if (!intersects) {
        return std::nullopt;
    }

    const Vector3f &intersectionPoint = ray.startPoint + ray.direction * t;
    if (exceedsAperture(intersectionPoint, surface.apertureRadius)) {
        return std::nullopt;
    }

    return LensSurfaceIntersection(intersectionPoint, normal);
}

bool CameraLens::exceedsAperture(const LensSurface &surface, const Ray &ray) const {
    const float t = (getSurfaceCenter(surface) - ray.startPoint.z) / ray.direction.z;
    Vector3f intersectionPosition = ray.constructIntersectionPoint(t);
    return exceedsAperture(intersectionPosition, apertureRadius);
}

bool CameraLens::exceedsAperture(const Vector3f &intersectionPosition, float apertureRadius) const {
    const float radiusOfIntersectionSquared = intersectionPosition.xy().lengthSquared();
    const float apertureRadiusSquared = apertureRadius * apertureRadius;
    const bool rayExceedsAperture = radiusOfIntersectionSquared > apertureRadiusSquared;
    return rayExceedsAperture;
}

bool CameraLens::hasAsphericSurfaces() const {
    return !asphericCoefficients.empty();
}

float CameraLens::length() const {
    float length = 0;
    for (auto &surface : surfaces) {
        length += surface.thickness;
    }
    return length;
}

std::vector<Vector3f> CameraLens::traceAndRecordFromFilmToWorld(const Ray &ray, float wavelength) const {
    std::vector<Vector3f> recordedPoints;
    recordedPoints.reserve(surfaces.size() + 2);

    Ray tracedRay = {{ray.startPoint.x, ray.startPoint.y, -ray.startPoint.z},
                     {ray.direction.x, ray.direction.y, -ray.direction.z}};
    recordedPoints.push_back(tracedRay.startPoint);
    for (int i = surfaces.size() - 1; i >= 0; i--) {
        auto surface = surfaces[i];
        if (surface.isAperture()) {
            if (exceedsAperture(surface, ray)) {
                return recordedPoints;
            }
            continue;
        }

        auto resultIntersection = intersect(surface, tracedRay);
        if (!resultIntersection) {
            return recordedPoints;
        }
        float eta_i = surface.material.getIor(wavelength);
        float eta_t = (i > 0 && surfaces[i - 1].material.getIor(wavelength) != 0)
                          ? surfaces[i - 1].material.getIor(wavelength)
                          : 1;

        auto result = refract(*resultIntersection, tracedRay, eta_t, eta_i);

        tracedRay = {result.startPoint, result.direction.invert()};
        recordedPoints.push_back(tracedRay.startPoint);
    }
    recordedPoints.push_back(tracedRay.constructIntersectionPoint(5));
    return recordedPoints;
}

float CameraLens::getSurfacesOffset() const {
    return surfacesOffset;
}

void CameraLens::zoom(float focalLength_mm) {
    if (variableLensDistances.empty()) {
        return;
    }

    const auto indexAndWeight = variableLensDistances.getFirstSampleIndex(focalLength_mm);

    for (auto &sampledDistance : variableLensDistances.sampledDistances) {
        const float interpolatedThickness = sampledDistance.getDistance(indexAndWeight);
        auto &surface = surfaces[sampledDistance.surfaceIndex];
        surface.thickness = interpolatedThickness;
    }

    initSurfaceCenters();

    initializeLensProperties();
}

} // crayg