#pragma once
#include "FilmAccumulationBuffer.h"
#include "FilmSumBuffer.h"
#include "FilmValueBuffer.h"
#include "image/PixelFormat.h"
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

    static std::optional<SumBufferVariantPtr> getAsSumBufferVariantPtr(const FilmBufferVariantPtr &bufferVariantPtr);

    static PixelFormat getPixelFormat(const FilmBufferVariantPtr &variantPtr);
    static int getChannelCount(const FilmBufferVariantPtr &variantPtr);
    static void *getDataPtr(const FilmBufferVariantPtr &variantPtr);
    static int getWidth(const FilmBufferVariantPtr &variantPtr);
    static int getHeight(const FilmBufferVariantPtr &variantPtr);
    static Resolution getResolution(const FilmBufferVariantPtr &variantPtr);
};

}
