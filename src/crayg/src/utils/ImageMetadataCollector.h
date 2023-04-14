#ifndef CRAYG_SRC_CRAYG_SRC_UTILS_IMAGEMETADATACOLLECTOR_H_
#define CRAYG_SRC_CRAYG_SRC_UTILS_IMAGEMETADATACOLLECTOR_H_

#include "image/ImageMetadata.h"
#include "scene/RenderSettings.h"
#include "scene/Scene.h"
#include <optional>

namespace crayg {

class ImageMetadataCollector {
  public:
    ImageMetadataCollector();
    ImageMetadataCollector(const std::optional<std::chrono::seconds> &renderTime, Scene *scene);

    std::optional<std::chrono::seconds> renderTime;
    Scene *scene = nullptr;

    ImageMetadata collectMetadata();

  private:
    void collectCraygVersion(ImageMetadata &imageMetadata) const;
    void collectCpuName(ImageMetadata &imageMetadata) const;
    void collectRenderTimeIfPresent(ImageMetadata &imageMetadata);
    void collectRenderSettingsIfPresent(ImageMetadata &imageMetadata);
    void collectIntegratorSettings(ImageMetadata &imageMetadata);
    void collectCamera(ImageMetadata &imageMetadata);
    void collectSceneStats(ImageMetadata &imageMetadata);
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_UTILS_IMAGEMETADATACOLLECTOR_H_
