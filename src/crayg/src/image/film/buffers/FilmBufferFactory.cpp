#include "FilmBufferFactory.h"

namespace crayg {

FilmBufferVariantPtr FilmBufferFactory::createValueBuffer(const Resolution &resolution, FilmPixelDepth filmPixelDepth,
                                                          int channelCount) {
    if (filmPixelDepth == FilmPixelDepth::FLOAT && channelCount == 1) {
        return new FloatValueBuffer(resolution);
    } else if (filmPixelDepth == FilmPixelDepth::FLOAT && channelCount == 3) {
        return new Color3fValueBuffer(resolution);
    } else if (filmPixelDepth == FilmPixelDepth::UINT8 && channelCount == 1) {
        return new IntValueBuffer(resolution);
    } else if (filmPixelDepth == FilmPixelDepth::UINT8 && channelCount == 3) {
        return new Color3iValueBuffer(resolution);
    }
    CRAYG_LOG_AND_THROW_MESSAGE(
        fmt::format("Can not create value buffer with depth {} and channel count {}", filmPixelDepth, channelCount));
}

FilmBufferVariantPtr FilmBufferFactory::createAccumulationBuffer(const Resolution &resolution,
                                                                 FilmPixelDepth filmPixelDepth, int channelCount) {
    if (filmPixelDepth == FilmPixelDepth::FLOAT && channelCount == 1) {
        return new FloatAccumulationBuffer(resolution);
    } else if (filmPixelDepth == FilmPixelDepth::FLOAT && channelCount == 3) {
        return new Color3fAccumulationBuffer(resolution);
    }
    CRAYG_LOG_AND_THROW_MESSAGE(
        fmt::format("Can not create value buffer with depth {} and channel count {}", filmPixelDepth, channelCount));
}
}