#pragma once

#include "basics/Color.h"
#include "image/BucketImageBuffer.h"
#include "image/ImageSpec.h"
#include "image/film/Film.h"

namespace crayg {

class BucketSampler {
  public:
    BucketSampler(int maxSamples, const std::function<Color(Vector2f)> &renderSample);
    virtual void sampleBucket(const ImageBucket &imageBucket) const = 0;
    virtual void addRequiredImageSpecs(ImageSpecBuilder &imageSpecBuilder) const = 0;
    virtual ~BucketSampler() = default;
    void setFilm(Film &film);

  protected:
    Film *film;
    int maxSamples;
    std::function<Color(Vector2f)> renderSample;
};

}
