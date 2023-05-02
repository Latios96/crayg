#ifndef CRAYG_SRC_CRAYG_SRC_RENDERER_BUCKETSAMPLERS_BUCKETSAMPLERFACTORY_H_
#define CRAYG_SRC_CRAYG_SRC_RENDERER_BUCKETSAMPLERS_BUCKETSAMPLERFACTORY_H_

#include "BucketSampler.h"
#include "scene/RenderSettings.h"
#include <memory>

namespace crayg {

class BucketSamplerFactory {
  public:
    static std::unique_ptr<BucketSampler> createBucketSampler(const RenderSettings &renderSettings,
                                                              const std::function<Color(Vector2f)> &renderSample);
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_RENDERER_BUCKETSAMPLERS_BUCKETSAMPLERFACTORY_H_
