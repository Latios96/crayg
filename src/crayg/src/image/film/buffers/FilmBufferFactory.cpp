#include "FilmBufferFactory.h"

namespace crayg {

FilmBufferVariantPtr FilmBufferFactory::createFilmBuffer(const Resolution &resolution, FilmBufferType bufferType,
                                                         FilmPixelDepth pixelDepth, int channelCount) {
    switch (bufferType) {
    case FilmBufferType::VALUE:
        return createValueBuffer(resolution, pixelDepth, channelCount);
    case FilmBufferType::ACCUMULATION:
        return createAccumulationBuffer(resolution, pixelDepth, channelCount);
    default:
        CRAYG_LOG_AND_THROW_MESSAGE(fmt::format("Unsupported buffer type {}", bufferType));
    }
}

FilmBufferVariantPtr FilmBufferFactory::createValueBuffer(const Resolution &resolution, FilmPixelDepth filmPixelDepth,
                                                          int channelCount) {
    if (filmPixelDepth == FilmPixelDepth::FLOAT32 && channelCount == 1) {
        return new FloatValueBuffer(resolution);
    } else if (filmPixelDepth == FilmPixelDepth::FLOAT32 && channelCount == 3) {
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
    if (filmPixelDepth == FilmPixelDepth::FLOAT32 && channelCount == 1) {
        return new FloatAccumulationBuffer(resolution);
    } else if (filmPixelDepth == FilmPixelDepth::FLOAT32 && channelCount == 3) {
        return new Color3fAccumulationBuffer(resolution);
    }
    CRAYG_LOG_AND_THROW_MESSAGE(
        fmt::format("Can not create value buffer with depth {} and channel count {}", filmPixelDepth, channelCount));
}

}