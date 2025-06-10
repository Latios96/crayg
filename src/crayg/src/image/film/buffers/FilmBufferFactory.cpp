#include "FilmBufferFactory.h"

namespace crayg {

FilmBufferVariantPtr FilmBufferFactory::createFilmBuffer(const Resolution &resolution, FilmBufferType bufferType,
                                                         FilmPixelDepth pixelDepth, int channelCount) {
    switch (bufferType) {
    case FilmBufferType::VALUE:
        return createValueBuffer(resolution, pixelDepth, channelCount);
    case FilmBufferType::ACCUMULATION:
        return createAccumulationBuffer(resolution, pixelDepth, channelCount);
    case FilmBufferType::SUM:
        return createSumBuffer(resolution, pixelDepth, channelCount);
    default:
        CRAYG_LOG_AND_THROW_RUNTIME_ERROR("Unsupported buffer type {}", bufferType);
    }
}

FilmBufferVariantPtr FilmBufferFactory::createValueBuffer(const Resolution &resolution, FilmPixelDepth filmPixelDepth,
                                                          int channelCount) {
    if (filmPixelDepth == FilmPixelDepth::FLOAT32 && channelCount == 1) {
        return new FloatValueBuffer(resolution);
    }
    if (filmPixelDepth == FilmPixelDepth::FLOAT32 && channelCount == 3) {
        return new Color3fValueBuffer(resolution);
    }
    if (filmPixelDepth == FilmPixelDepth::UINT8 && channelCount == 1) {
        return new IntValueBuffer(resolution);
    }
    if (filmPixelDepth == FilmPixelDepth::UINT8 && channelCount == 3) {
        return new Color3iValueBuffer(resolution);
    }
    CRAYG_LOG_AND_THROW_RUNTIME_ERROR("Can not create value buffer with depth {} and channel count {}", filmPixelDepth,
                                      channelCount);
}

FilmBufferVariantPtr FilmBufferFactory::createAccumulationBuffer(const Resolution &resolution,
                                                                 FilmPixelDepth filmPixelDepth, int channelCount) {
    if (filmPixelDepth == FilmPixelDepth::FLOAT32 && channelCount == 1) {
        return new FloatAccumulationBuffer(resolution);
    }
    if (filmPixelDepth == FilmPixelDepth::FLOAT32 && channelCount == 3) {
        return new Color3fAccumulationBuffer(resolution);
    }
    CRAYG_LOG_AND_THROW_RUNTIME_ERROR("Can not create value buffer with depth {} and channel count {}", filmPixelDepth,
                                      channelCount);
}

FilmBufferVariantPtr FilmBufferFactory::createSumBuffer(const Resolution &resolution, FilmPixelDepth filmPixelDepth,
                                                        int channelCount) {
    if (filmPixelDepth == FilmPixelDepth::FLOAT32 && channelCount == 1) {
        return new FloatSumBuffer(resolution);
    }
    if (filmPixelDepth == FilmPixelDepth::FLOAT32 && channelCount == 3) {
        return new Color3fSumBuffer(resolution);
    }
    if (filmPixelDepth == FilmPixelDepth::UINT8 && channelCount == 1) {
        return new IntSumBuffer(resolution);
    }
    if (filmPixelDepth == FilmPixelDepth::UINT8 && channelCount == 3) {
        return new Color3iSumBuffer(resolution);
    }
    CRAYG_LOG_AND_THROW_RUNTIME_ERROR("Can not create value buffer with depth {} and channel count {}", filmPixelDepth,
                                      channelCount);
}

}