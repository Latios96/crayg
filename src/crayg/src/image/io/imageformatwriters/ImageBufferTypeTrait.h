#pragma once
#include "image/PixelBuffer.h"
#include "image/film/buffers/FilmBufferVariants.h"

namespace crayg {

template <typename ImageBufferType> struct ImageBufferTypeTrait {
    static int getWidth(const ImageBufferType &bufferType);
    static int getHeight(const ImageBufferType &bufferType);
    static PixelFormat getPixelFormat(const ImageBufferType &bufferType);
    static int getColorChannelCount(const ImageBufferType &bufferType);
    static void *getDataPtr(const ImageBufferType &bufferType);
};

template <> struct ImageBufferTypeTrait<PixelBuffer> {
    static int getWidth(const PixelBuffer &pixelBuffer) {
        return pixelBuffer.getWidth();
    }

    static int getHeight(const PixelBuffer &pixelBuffer) {
        return pixelBuffer.getHeight();
    }

    static PixelFormat getPixelFormat(const PixelBuffer &pixelBuffer) {
        return pixelBuffer.getPixelFormat();
    }

    static int getColorChannelCount(const PixelBuffer &pixelBuffer) {
        return pixelBuffer.getColorChannelCount();
    }

    static void *getDataPtr(const PixelBuffer &pixelBuffer) {
        return std::visit([](auto ptr) { return (void *)ptr; }, pixelBuffer.getData());
    }
};

template <> struct ImageBufferTypeTrait<FilmBufferVariantPtr> {
    static int getWidth(const FilmBufferVariantPtr &filmBufferVariant) {
        return FilmBufferVariants::getWidth(filmBufferVariant);
    }

    static int getHeight(const FilmBufferVariantPtr &filmBufferVariant) {
        return FilmBufferVariants::getHeight(filmBufferVariant);
    }

    static PixelFormat getPixelFormat(const FilmBufferVariantPtr &filmBufferVariant) {
        return FilmBufferVariants::getPixelFormat(filmBufferVariant);
    }

    static int getColorChannelCount(const FilmBufferVariantPtr &filmBufferVariant) {
        return FilmBufferVariants::getChannelCount(filmBufferVariant);
    }

    static void *getDataPtr(const FilmBufferVariantPtr &filmBufferVariant) {
        return FilmBufferVariants::getDataPtr(filmBufferVariant);
    }
};

}
