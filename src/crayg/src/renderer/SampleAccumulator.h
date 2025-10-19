#pragma once

#include "crayg/foundation/math/geometry/Color.h"

namespace crayg {

class SampleAccumulator {
  public:
    SampleAccumulator();
    void addSample(const Color &color);
    Color getValue();

  private:
    int sampleCount;
    Color sum;
};

}
