#include "LensRaytracerTracer.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace crayg {

LensRaytracerTracer::LensRaytracerTracer(const std::string &traceName, const CameraLens &cameraLens)
    : traceName(traceName), cameraLens(cameraLens) {
}

void LensRaytracerTracer::collect(const Ray &ray) {
    collect(ray, {});
}

void LensRaytracerTracer::collect(const Ray &ray, const Vector3f &normal) {
    events.push_back({ray.startPoint, ray.direction, normal});
}

void LensRaytracerTracer::emit() {
    emit(std::filesystem::current_path());
}

void LensRaytracerTracer::emit(const std::filesystem::path &path) {
    json j = json{{"traceName", traceName}, {"unit", "centimeters"}};

    auto jsonEvents = json::array();
    for (auto &event : events) {
        jsonEvents.push_back({{"point", {event.point.x, event.point.y, event.point.z}},
                              {"direction", {event.direction.x, event.direction.y, event.direction.z}},
                              {"normal", {event.normal.x, event.normal.y, event.normal.z}}});
    }
    j["events"] = jsonEvents;

    auto jsonLensSurfaces = json::array();
    for (auto &surface : cameraLens.surfaces) {
        jsonLensSurfaces.push_back({
            {"curvatureRadius", surface.curvatureRadius},
            {"thickness", surface.thickness},
            {"ior", surface.ior},
            {"apertureRadius", surface.apertureRadius},
            {"center", surface.center},
        });
    }
    j["lens"]["name"] = cameraLens.metadata.name;
    j["lens"]["surfaces"] = jsonLensSurfaces;

    auto jsonFilePath = path / fmt::format("{}.json", traceName);
    std::ofstream o(jsonFilePath.string());
    o << std::setw(4) << j << std::endl;
    o.close();
}
} // crayg