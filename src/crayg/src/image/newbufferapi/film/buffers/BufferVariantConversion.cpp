#include "BufferVariantConversion.h"

namespace crayg {

std::optional<AccumulationBufferVariantPtr>
crayg::BufferVariantConversion::getAsAccumulationBufferVariantPtr(const FilmBufferVariantPtr &bufferVariantPtr) {
    if (std::holds_alternative<FloatAccumulationBuffer *>(bufferVariantPtr)) {
        return std::get<FloatAccumulationBuffer *>(bufferVariantPtr);
    } else if (std::holds_alternative<Color3fAccumulationBuffer *>(bufferVariantPtr)) {
        return std::get<Color3fAccumulationBuffer *>(bufferVariantPtr);
    }
    return std::nullopt;
}

std::optional<ValueBufferVariantPtr>
crayg::BufferVariantConversion::getAsValueBufferVariantPtr(const FilmBufferVariantPtr &bufferVariantPtr) {
    if (std::holds_alternative<FloatValueBuffer *>(bufferVariantPtr)) {
        return std::get<FloatValueBuffer *>(bufferVariantPtr);
    } else if (std::holds_alternative<IntValueBuffer *>(bufferVariantPtr)) {
        return std::get<IntValueBuffer *>(bufferVariantPtr);
    } else if (std::holds_alternative<Color3fValueBuffer *>(bufferVariantPtr)) {
        return std::get<Color3fValueBuffer *>(bufferVariantPtr);
    } else if (std::holds_alternative<Color3iValueBuffer *>(bufferVariantPtr)) {
        return std::get<Color3iValueBuffer *>(bufferVariantPtr);
    }
    return std::nullopt;
}

}
