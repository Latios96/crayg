#pragma once

#include "basics/Color.h"

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

} // crayg
