#pragma once
#include "AccumulationBuffer.h"
#include "FilmPixelDepth.h"
#include "ValueBuffer.h"
#include "utils/Exceptions.h"
#include <optional>

namespace crayg {

#define EnumerateAllFilmBuffers EnumerateAllValueBuffers, EnumerateAllAccumulationBuffers
#define EnumerateAllFilmBufferPtrs EnumerateAllValueBufferPtrs, EnumerateAllAccumulationBufferPtrs

typedef std::variant<EnumerateAllFilmBuffers> FilmBufferVariant;
typedef std::variant<EnumerateAllFilmBufferPtrs> FilmBufferVariantPtr;

inline void freeFilmBufferVariantPtr(FilmBufferVariantPtr &ptr) {
    std::visit([](auto *buf) { delete buf; }, ptr);
}

}
