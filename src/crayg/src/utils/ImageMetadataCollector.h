#ifndef CRAYG_SRC_CRAYG_SRC_UTILS_IMAGEMETADATACOLLECTOR_H_
#define CRAYG_SRC_CRAYG_SRC_UTILS_IMAGEMETADATACOLLECTOR_H_

#include "image/ImageMetadata.h"
namespace crayg {

class ImageMetadataCollector {
 public:
    ImageMetadataCollector();
    ImageMetadataCollector(const std::optional<std::chrono::seconds> &renderTime,
                           const std::optional<RenderSettings> &renderSettings);

    std::optional<std::chrono::seconds> renderTime;
    std::optional<RenderSettings> renderSettings;

    ImageMetadata collectMetadata();

 private:
    void collectCraygVersion(ImageMetadata &imageMetadata) const;
    void collectCpuName(ImageMetadata &imageMetadata) const;
    void collectRenderTimeIfPresent(ImageMetadata &imageMetadata);
    void collectRenderSettingsIfPresent(ImageMetadata &imageMetadata);
    void collectIntegratorSettings(ImageMetadata &imageMetadata);
};

} // crayg

#endif //CRAYG_SRC_CRAYG_SRC_UTILS_IMAGEMETADATACOLLECTOR_H_
