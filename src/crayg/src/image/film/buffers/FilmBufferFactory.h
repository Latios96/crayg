#pragma once

#include "FilmBufferVariants.h"
#include "image/film/Film.h"

namespace crayg {
class FilmBufferFactory {
  public:
    static FilmBufferVariantPtr createFilmBuffer(const Resolution &resolution, FilmBufferType filmBuffer,
                                                 FilmPixelDepth pixelDepth, int channelCount);
    static FilmBufferVariantPtr createValueBuffer(const Resolution &resolution, FilmPixelDepth filmPixelDepth,
                                                  int channelCount);

    static FilmBufferVariantPtr createAccumulationBuffer(const Resolution &resolution, FilmPixelDepth filmPixelDepth,
                                                         int channelCount);

    static FilmBufferVariantPtr createSumBuffer(const Resolution &resolution, FilmPixelDepth filmPixelDepth,
                                                int channelCount);
};
}
