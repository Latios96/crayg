#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_REALISTIC_CAMERALENSMETADATA_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_REALISTIC_CAMERALENSMETADATA_H_

#include <fmt/ostream.h>
#include <string>

namespace crayg {

struct CameraLensMetadata {
    CameraLensMetadata() = default;
    explicit CameraLensMetadata(const std::string &name);
    CameraLensMetadata(const std::string &name, float focalLength, float maximumAperture, bool isAnamorphic,
                       float squeeze, int lensCount, float closestFocalDistance, const std::string &patent,
                       const std::string &description);
    std::string name;
    float focalLength = 0;
    float maximumAperture = 0;
    bool isAnamorphic = false;
    float squeeze = 1;
    int elementCount = 0;
    float closestFocalDistance = 0;
    std::string patent;
    std::string description;

    bool operator==(const CameraLensMetadata &rhs) const;
    bool operator!=(const CameraLensMetadata &rhs) const;
    friend std::ostream &operator<<(std::ostream &os, const CameraLensMetadata &metadata);
};

} // crayg

template <> struct fmt::formatter<crayg::CameraLensMetadata> : ostream_formatter {};

#endif // CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_REALISTIC_CAMERALENSMETADATA_H_
