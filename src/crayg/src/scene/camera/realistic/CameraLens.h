#pragma once

#include "CameraLensMetadata.h"
#include "LensGeometry.h"
#include "LensMaterial.h"
#include "LensSurface.h"
#include "ThickLensApproximation.h"
#include "VariableLensDistances.h"
#include "basics/Gradient.h"
#include "basics/Ray.h"
#include "basics/Vector3f_formatter.h"
#include "crayg/foundation/objects/DtoUtils.h"
#include <fmt/ostream.h>
#include <functional>
#include <optional>
#include <ostream>
#include <string>
#include <vector>

namespace crayg {

CRAYG_DTO_2(LensSurfaceIntersection, Vector3f, point, Vector3f, normal);

struct CameraLens {
    std::vector<LensSurface> surfaces;
    std::vector<AsphericCoefficients> asphericCoefficients;
    VariableLensDistances variableLensDistances;
    ThickLensApproximation thickLensApproximation;
    CameraLensMetadata metadata;

    CameraLens(const CameraLensMetadata &metadata, const std::vector<LensSurface> &surfaces);
    CameraLens(const CameraLensMetadata &metadata, const std::vector<LensSurface> &surfaces,
               const std::vector<AsphericCoefficients> &asphericCoefficients,
               const VariableLensDistances &variableLensDistances);
    CameraLens(const CameraLens &cameraLens);

    const LensSurface &getFirstSurface() const;
    const LensSurface &getLastSurface() const;
    LensSurface &getAperture();
    float getApertureRadius() const;
    float length() const;
    bool hasAsphericSurfaces() const;
    bool hasVariableDistances() const;
    float getSurfacesOffset() const;
    float getSurfaceCenter(const LensSurface &lensSurface) const;

    void focusLens(float focalDistance);
    void changeAperture(float fStop);
    void zoom(float focalLength_mm);
    std::optional<Ray> traceUntil(const Ray &inputRay, int startIndex, int endIndex, int increment, float wavelength,
                                  Vector3f *surfaceNormal);
    std::optional<Ray> traceFromFilmToWorld(const Ray &ray, float wavelength) const;
    std::optional<Ray> traceFromFilmToWorld(const Ray &ray, float wavelength,
                                            float *maxRelativeDistanceToOpticalAxis) const;
    std::optional<Ray> traceFromWorldToFilm(const Ray &ray, float wavelength) const;

    void traceAndRecordFromWorldToFilm(std::vector<Vector3f> &recordedPoints, const Ray &ray, float wavelength) const;
    void traceAndRecordFromFilmToWorld(std::vector<Vector3f> &recordedPoints, const Ray &ray, float wavelength) const;

    Ray refract(const LensSurfaceIntersection &intersection, const Ray &ray, float iorIn, float iorOut) const;

    bool operator==(const CameraLens &rhs) const;
    bool operator!=(const CameraLens &rhs) const;
    friend std::ostream &operator<<(std::ostream &os, const CameraLens &lens);

  private:
    void initializeLensMaterials();
    void initSurfaceCenters();
    void initializeLensProperties();
    void calculateMetadata();
    void handleAnamorphicFocussing();
    float computeClosestFocalDistance() const;
    float calculateSurfaceOffset(float focalDistance) const;

    std::optional<LensSurfaceIntersection> intersect(const LensSurface &surface, const Ray &ray) const;
    bool exceedsAperture(const LensSurface &surface, const Ray &ray) const;
    bool exceedsAperture(const Vector3f &intersectionPosition, float apertureRadius) const;

  public:
    int apertureIndex = -1;
    float apertureRadius;
    float surfacesOffset = 0;
};

}
