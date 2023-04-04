#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_LENSRAYTRACERTRACER_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_LENSRAYTRACERTRACER_H_

#include "CameraLens.h"
#include "basics/Ray.h"
#include "basics/Vector3f.h"
#include <fmt/format.h>
#include <vector>

namespace boost {
namespace filesystem {
class path;
}
}

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
    void emit(const boost::filesystem::path &path);
};
}
#endif // CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_LENSRAYTRACERTRACER_H_
