#pragma once
#include "FilmAccumulationBuffer.h"
#include "FilmPixelDepth.h"
#include "FilmSumBuffer.h"
#include "FilmValueBuffer.h"
#include "utils/Exceptions.h"
#include <optional>

namespace crayg {

#define EnumerateAllFilmBuffers EnumerateAllValueBuffers, EnumerateAllAccumulationBuffers, EnumerateAllSumBuffers
#define EnumerateAllFilmBufferPtrs                                                                                     \
    EnumerateAllValueBufferPtrs, EnumerateAllAccumulationBufferPtrs, EnumerateAllSumBufferPtrs

typedef std::variant<EnumerateAllFilmBuffers> FilmBufferVariant;
typedef std::variant<EnumerateAllFilmBufferPtrs> FilmBufferVariantPtr;

class FilmBufferVariants {
  public:
    static void freeFilmBufferVariantPtr(const FilmBufferVariantPtr &ptr);

    static std::optional<AccumulationBufferVariantPtr>
    getAsAccumulationBufferVariantPtr(const FilmBufferVariantPtr &bufferVariantPtr);

    static std::optional<ValueBufferVariantPtr>
    getAsValueBufferVariantPtr(const FilmBufferVariantPtr &bufferVariantPtr);

    static FilmPixelDepth getPixelDepth(const FilmBufferVariantPtr &variantPtr);
    static int getChannelCount(const FilmBufferVariantPtr &variantPtr);
    static void *getDataPtr(const FilmBufferVariantPtr &variantPtr);
};

}
