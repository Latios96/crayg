#include "SampleAccumulator.h"

namespace crayg {
SampleAccumulator::SampleAccumulator() : sampleCount(0), sum(Color::createBlack()) {
}

void SampleAccumulator::addSample(const Color &color) {
    sum = sum + color;
    sampleCount++;
}

Color SampleAccumulator::getValue() {
    return sum / static_cast<float>(sampleCount);
}

}