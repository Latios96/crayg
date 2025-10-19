#pragma once

#include "CameraLens.h"
#include "crayg/foundation/math/geometry/Ray.h"
#include "crayg/foundation/math/geometry/Vector3f.h"
#include <filesystem>
#include <fmt/format.h>
#include <vector>

namespace crayg {

class LensRaytracerTracer {
    struct TraceEvent {
        Vector3f point, direction, normal;
    };

    std::vector<TraceEvent> events;
    std::string traceName;
    const CameraLens &cameraLens;

  public:
    explicit LensRaytracerTracer(const std::string &traceName, const CameraLens &cameraLens);

    void collect(const Ray &ray);

    void collect(const Ray &ray, const Vector3f &normal);

    void emit();
    void emit(const std::filesystem::path &path);
};
}
