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

PixelFormat FilmBufferVariants::getPixelFormat(const FilmBufferVariantPtr &variantPtr) {
    return std::visit([](auto buf) { return buf->pixelFormat; }, variantPtr);
}

int FilmBufferVariants::getChannelCount(const FilmBufferVariantPtr &variantPtr) {
    return std::visit([](auto buf) { return buf->chCount; }, variantPtr);
}

void *FilmBufferVariants::getDataPtr(const FilmBufferVariantPtr &variantPtr) {
    return std::visit([](auto buf) { return (void *)buf->data; }, variantPtr);
}

}
