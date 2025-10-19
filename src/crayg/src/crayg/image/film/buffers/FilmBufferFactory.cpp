#include "FilmBufferFactory.h"

namespace crayg {

FilmBufferVariantPtr FilmBufferFactory::createFilmBuffer(const Resolution &resolution, FilmBufferType bufferType,
                                                         PixelFormat pixelFormat, int channelCount) {
    switch (bufferType) {
    case FilmBufferType::VALUE:
        return createValueBuffer(resolution, pixelFormat, channelCount);
    case FilmBufferType::ACCUMULATION:
        return createAccumulationBuffer(resolution, pixelFormat, channelCount);
    case FilmBufferType::SUM:
        return createSumBuffer(resolution, pixelFormat, channelCount);
    default:
        CRAYG_LOG_AND_THROW_RUNTIME_ERROR("Unsupported buffer type {}", bufferType);
    }
}

FilmBufferVariantPtr FilmBufferFactory::createValueBuffer(const Resolution &resolution, PixelFormat pixelFormat,
                                                          int channelCount) {
    if (pixelFormat == PixelFormat::FLOAT32 && channelCount == 1) {
        return new FloatValueBuffer(resolution);
    }
    if (pixelFormat == PixelFormat::FLOAT32 && channelCount == 3) {
        return new Color3fValueBuffer(resolution);
    }
    if (pixelFormat == PixelFormat::UINT8 && channelCount == 1) {
        return new IntValueBuffer(resolution);
    }
    if (pixelFormat == PixelFormat::UINT8 && channelCount == 3) {
        return new Color3iValueBuffer(resolution);
    }
    CRAYG_LOG_AND_THROW_RUNTIME_ERROR("Can not create value buffer with depth {} and channel count {}", pixelFormat,
                                      channelCount);
}

FilmBufferVariantPtr FilmBufferFactory::createAccumulationBuffer(const Resolution &resolution, PixelFormat pixelFormat,
                                                                 int channelCount) {
    if (pixelFormat == PixelFormat::FLOAT32 && channelCount == 1) {
        return new FloatAccumulationBuffer(resolution);
    }
    if (pixelFormat == PixelFormat::FLOAT32 && channelCount == 3) {
        return new Color3fAccumulationBuffer(resolution);
    }
    CRAYG_LOG_AND_THROW_RUNTIME_ERROR("Can not create value buffer with depth {} and channel count {}", pixelFormat,
                                      channelCount);
}

FilmBufferVariantPtr FilmBufferFactory::createSumBuffer(const Resolution &resolution, PixelFormat pixelFormat,
                                                        int channelCount) {
    if (pixelFormat == PixelFormat::FLOAT32 && channelCount == 1) {
        return new FloatSumBuffer(resolution);
    }
    if (pixelFormat == PixelFormat::FLOAT32 && channelCount == 3) {
        return new Color3fSumBuffer(resolution);
    }
    if (pixelFormat == PixelFormat::UINT8 && channelCount == 1) {
        return new IntSumBuffer(resolution);
    }
    if (pixelFormat == PixelFormat::UINT8 && channelCount == 3) {
        return new Color3iSumBuffer(resolution);
    }
    CRAYG_LOG_AND_THROW_RUNTIME_ERROR("Can not create value buffer with depth {} and channel count {}", pixelFormat,
                                      channelCount);
}

}