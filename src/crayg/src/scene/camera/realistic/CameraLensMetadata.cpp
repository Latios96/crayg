#include "CameraLensMetadata.h"
#include "utils/ToStringHelper.h"

namespace crayg {

CameraLensMetadata::CameraLensMetadata(const std::string &name) : name(name) {
}

CameraLensMetadata::CameraLensMetadata(const std::string &name, float focalLength, float maximumAperture,
                                       bool isAnamorphic, float squeeze, int lensCount, float closestFocalDistance,
                                       const std::string &patent, const std::string &description)
    : name(name), focalLength(focalLength), maximumAperture(maximumAperture), isAnamorphic(isAnamorphic),
      squeeze(squeeze), surfaceCount(lensCount), closestFocalDistance(closestFocalDistance), patent(patent),
      description(description) {
}

std::ostream &operator<<(std::ostream &os, const CameraLensMetadata &metadata) {
    os << ToStringHelper("CameraLensMetadata")
              .addMember("name", metadata.name)
              .addMember("focalLength", metadata.focalLength)
              .addMember("maximumAperture", metadata.maximumAperture)
              .addMember("isAnamorphic", metadata.isAnamorphic)
              .addMember("squeeze", metadata.squeeze)
              .addMember("surfaceCount", metadata.surfaceCount)
              .addMember("closestFocalDistance", metadata.closestFocalDistance)
              .addMember("patent", metadata.patent)
              .addMember("description", metadata.description)
              .finish();
    return os;
}

bool CameraLensMetadata::operator==(const CameraLensMetadata &rhs) const {
    return name == rhs.name && focalLength == rhs.focalLength && maximumAperture == rhs.maximumAperture &&
           isAnamorphic == rhs.isAnamorphic && squeeze == rhs.squeeze && surfaceCount == rhs.surfaceCount &&
           closestFocalDistance == rhs.closestFocalDistance && patent == rhs.patent && description == rhs.description;
}

bool CameraLensMetadata::operator!=(const CameraLensMetadata &rhs) const {
    return !(rhs == *this);
}

}