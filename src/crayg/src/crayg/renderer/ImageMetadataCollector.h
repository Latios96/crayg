#pragma once

#include "crayg/image/ImageMetadata.h"
#include "crayg/scene/RenderSettings.h"
#include "crayg/scene/Scene.h"
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

}
