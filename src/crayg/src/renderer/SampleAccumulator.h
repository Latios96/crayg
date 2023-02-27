#ifndef CRAYG_SRC_CRAYG_SRC_RENDERER_SAMPLEACCUMULATOR_H_
#define CRAYG_SRC_CRAYG_SRC_RENDERER_SAMPLEACCUMULATOR_H_

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

#endif // CRAYG_SRC_CRAYG_SRC_RENDERER_SAMPLEACCUMULATOR_H_
