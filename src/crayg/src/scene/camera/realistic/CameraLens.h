#pragma once

#include "CameraLensMetadata.h"
#include "LensGeometry.h"
#include "LensMaterial.h"
#include "LensSurface.h"
#include "ThickLensApproximation.h"
#include "basics/Gradient.h"
#include "basics/Ray.h"
#include "utils/DtoUtils.h"
#include <fmt/ostream.h>
#include <functional>
#include <optional>
#include <ostream>
#include <string>
#include <vector>

namespace crayg {

CRAYG_DTO_2(LensSurfaceIntersection, Vector3f, point, Vector3f, normal);

struct SurfaceDistances {
    int surfaceIndex;
    std::vector<float> distances;
};

struct CameraLens {
    CameraLens(const CameraLensMetadata &metadata, const std::vector<LensSurface> &surfaces);
    CameraLens(const CameraLensMetadata &metadata, const std::vector<LensSurface> &surfaces,
               const std::vector<AsphericCoefficients> &asphericCoefficients);
    CameraLens(const CameraLens &cameraLens);
    std::vector<LensSurface> surfaces;
    std::vector<AsphericCoefficients> asphericCoefficients;

    struct {
        std::vector<float> focalLengthSamples;
        std::vector<SurfaceDistances> distances;

    } variableDistances;

    // zoom to desired focallength, clamp range

    void zoom(float focalLength) {
        if (variableDistances.focalLengthSamples.empty()) {
            return;
        }
        const float firstFocalLength = variableDistances.focalLengthSamples[0];
        const float lastFocalLength =
            variableDistances.focalLengthSamples[variableDistances.focalLengthSamples.size() - 1];
        const float focalLengthDistance = lastFocalLength - firstFocalLength;
        focalLength = std::clamp(focalLength, firstFocalLength, lastFocalLength);
        const float relativeFocalLength = focalLength / focalLengthDistance;

        for (auto &surfaceDistance : variableDistances.distances) {
            std::vector<GradientStop<float>> stops;
            for (int i = 0; i < variableDistances.focalLengthSamples.size(); i++) {
                stops.emplace_back(variableDistances.focalLengthSamples[i], surfaceDistance.distances[i]);
            }
            Gradient<float> distanceGradient(stops);
            const float distanceForFocalLength = distanceGradient.interpolate(relativeFocalLength);
            surfaces[surfaceDistance.surfaceIndex].thickness = distanceForFocalLength;
        }

        // recompute centers
    }

    ThickLensApproximation thickLensApproximation;

    CameraLensMetadata metadata;

    const LensSurface &getFirstSurface() const;
    const LensSurface &getLastSurface() const;
    LensSurface &getAperture();
    float getApertureRadius() const;
    float length() const;

    std::optional<Ray> traceFromFilmToWorld(const Ray &ray, float wavelength) const;
    std::optional<Ray> traceFromFilmToWorld(const Ray &ray, float wavelength,
                                            float *maxRelativeDistanceToOpticalAxis) const;
    std::optional<Ray> traceFromWorldToFilm(const Ray &ray, float wavelength) const;
    std::vector<Vector3f> traceAndRecordFromWorldToFilm(const Ray &ray, float wavelength) const;
    std::vector<Vector3f> traceAndRecordFromFilmToWorld(const Ray &ray, float wavelength) const;

    void focusLens(float focalDistance);
    void changeAperture(float fStop);

    Ray refract(const LensSurfaceIntersection &intersection, const Ray &ray, float iorIn, float iorOut) const;
    bool hasAsphericSurfaces() const;
    float getSurfacesOffset() const;

    float getSurfaceCenter(const LensSurface &lensSurface) const {
        return lensSurface.center + surfacesOffset;
    }

    bool operator==(const CameraLens &rhs) const;
    bool operator!=(const CameraLens &rhs) const;
    friend std::ostream &operator<<(std::ostream &os, const CameraLens &lens);

  private:
    void initializeLensMaterials();
    void calculateMetadata();
    void handleAnamorphicFocussing();
    float computeClosestFocalDistance() const;
    float calculateSurfaceOffset(float focalDistance) const;

    std::optional<LensSurfaceIntersection> intersect(const LensSurface &surface, const Ray &ray) const;
    bool exceedsAperture(const LensSurface &surface, const Ray &ray) const;
    bool exceedsAperture(const Vector3f &intersectionPosition, float apertureRadius) const;

    int apertureIndex = -1;
    float apertureRadius;
    float surfacesOffset = 0;
};

} // crayg
