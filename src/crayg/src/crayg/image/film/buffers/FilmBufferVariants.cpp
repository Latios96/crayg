#include "FilmBufferVariants.h"

namespace crayg {

void FilmBufferVariants::freeFilmBufferVariantPtr(const FilmBufferVariantPtr &ptr) {
    std::visit([](auto *buf) { delete buf; }, ptr);
}

std::optional<AccumulationBufferVariantPtr>
FilmBufferVariants::getAsAccumulationBufferVariantPtr(const FilmBufferVariantPtr &bufferVariantPtr) {
    if (std::holds_alternative<FloatAccumulationBuffer *>(bufferVariantPtr)) {
        return std::get<FloatAccumulationBuffer *>(bufferVariantPtr);
    }
    if (std::holds_alternative<Color3fAccumulationBuffer *>(bufferVariantPtr)) {
        return std::get<Color3fAccumulationBuffer *>(bufferVariantPtr);
    }
    return std::nullopt;
}

std::optional<ValueBufferVariantPtr>
FilmBufferVariants::getAsValueBufferVariantPtr(const FilmBufferVariantPtr &bufferVariantPtr) {
    if (std::holds_alternative<FloatValueBuffer *>(bufferVariantPtr)) {
        return std::get<FloatValueBuffer *>(bufferVariantPtr);
    }
    if (std::holds_alternative<IntValueBuffer *>(bufferVariantPtr)) {
        return std::get<IntValueBuffer *>(bufferVariantPtr);
    }
    if (std::holds_alternative<Color3fValueBuffer *>(bufferVariantPtr)) {
        return std::get<Color3fValueBuffer *>(bufferVariantPtr);
    }
    if (std::holds_alternative<Color3iValueBuffer *>(bufferVariantPtr)) {
        return std::get<Color3iValueBuffer *>(bufferVariantPtr);
    }
    return std::nullopt;
}

std::optional<SumBufferVariantPtr>
FilmBufferVariants::getAsSumBufferVariantPtr(const FilmBufferVariantPtr &bufferVariantPtr) {
    if (std::holds_alternative<FloatSumBuffer *>(bufferVariantPtr)) {
        return std::get<FloatSumBuffer *>(bufferVariantPtr);
    }
    if (std::holds_alternative<IntSumBuffer *>(bufferVariantPtr)) {
        return std::get<IntSumBuffer *>(bufferVariantPtr);
    }
    if (std::holds_alternative<Color3fSumBuffer *>(bufferVariantPtr)) {
        return std::get<Color3fSumBuffer *>(bufferVariantPtr);
    }
    if (std::holds_alternative<Color3iSumBuffer *>(bufferVariantPtr)) {
        return std::get<Color3iSumBuffer *>(bufferVariantPtr);
    }
    return std::nullopt;
}

PixelFormat FilmBufferVariants::getPixelFormat(const FilmBufferVariantPtr &variantPtr) {
    return std::visit([](auto buf) { return buf->pixelFormat; }, variantPtr);
}

int FilmBufferVariants::getChannelCount(const FilmBufferVariantPtr &variantPtr) {
    return std::visit([](auto buf) { return buf->chCount; }, variantPtr);
}

void *FilmBufferVariants::getDataPtr(const FilmBufferVariantPtr &variantPtr) {
    return std::visit([](auto buf) { return (void *)buf->data; }, variantPtr);
}

int FilmBufferVariants::getWidth(const FilmBufferVariantPtr &variantPtr) {
    return std::visit([](auto buf) { return buf->width; }, variantPtr);
}

int FilmBufferVariants::getHeight(const FilmBufferVariantPtr &variantPtr) {
    return std::visit([](auto buf) { return buf->height; }, variantPtr);
}

Resolution FilmBufferVariants::getResolution(const FilmBufferVariantPtr &variantPtr) {
    return std::visit([](auto buf) { return Resolution(buf->width, buf->height); }, variantPtr);
}

}
