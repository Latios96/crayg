#pragma once

#include "FilmBufferVariants.h"

namespace crayg {
class FilmBufferFactory {
  public:
    static FilmBufferVariantPtr createValueBuffer(const Resolution &resolution, FilmPixelDepth filmPixelDepth,
                                                  int channelCount);

    static FilmBufferVariantPtr createAccumulationBuffer(const Resolution &resolution, FilmPixelDepth filmPixelDepth,
                                                         int channelCount);
};
}
