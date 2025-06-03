#pragma once
#include "FilmBufferVariants.h"
#include <optional>

namespace crayg {

class BufferVariantConversion {
  public:
    static std::optional<AccumulationBufferVariantPtr>
    getAsAccumulationBufferVariantPtr(const FilmBufferVariantPtr &bufferVariantPtr);

    static std::optional<ValueBufferVariantPtr>
    getAsValueBufferVariantPtr(const FilmBufferVariantPtr &bufferVariantPtr);
};

}
