#pragma once

#include "BucketSampler.h"
#include "scene/RenderSettings.h"
#include <memory>

namespace crayg {

class BucketSamplerFactory {
  public:
    static std::unique_ptr<BucketSampler> createBucketSampler(const RenderSettings &renderSettings,
                                                              const std::function<Color(Vector2f)> &renderSample);
};

}
