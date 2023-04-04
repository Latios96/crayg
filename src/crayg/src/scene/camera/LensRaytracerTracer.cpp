#include "LensRaytracerTracer.h"
#include <boost/filesystem.hpp>
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
    emit(boost::filesystem::current_path());
}

void LensRaytracerTracer::emit(const boost::filesystem::path &path) {
    json j = json{{"traceName", traceName}, {"unit", "centimeters"}};

    auto jsonEvents = json::array();
    for (auto &event : events) {
        jsonEvents.push_back({{"point", {event.point.x, event.point.y, event.point.z}},
                              {"direction", {event.direction.x, event.direction.y, event.direction.z}},
                              {"normal", {event.normal.x, event.normal.y, event.normal.z}}});
    }
    j["events"] = jsonEvents;

    auto jsonLensElements = json::array();
    for (auto &element : cameraLens.elements) {
        jsonLensElements.push_back({
            {"curvatureRadius", element.curvatureRadius},
            {"thickness", element.thickness},
            {"ior", element.ior},
            {"apertureRadius", element.apertureRadius},
            {"center", element.center},
        });
    }
    j["lens"]["name"] = cameraLens.name;
    j["lens"]["elements"] = jsonLensElements;

    auto jsonFilePath = path / fmt::format("{}.json", traceName);
    std::ofstream o(jsonFilePath.string());
    o << std::setw(4) << j << std::endl;
    o.close();
}
} // crayg