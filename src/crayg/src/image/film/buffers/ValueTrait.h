#pragma once
#include "FilmPixelDepth.h"

#include <algorithm>
#include <cstdint>
#include <string_view>

namespace crayg {

template <typename T> struct ValueTrait {
    static float toFloat(const T &value);
    static T fromFloat(const float &value);
};

template <> struct ValueTrait<float> {
    static float toFloat(const float &value) {
        return value;
    }

    static float fromFloat(const float &value) {
        return value;
    }

    static constexpr std::string_view name = "f32";
    static constexpr FilmPixelDepth pixelDepth = FilmPixelDepth::FLOAT32;
};

template <> struct ValueTrait<uint8_t> {
    static float toFloat(const uint8_t &value) {
        return static_cast<float>(value) / 255.f;
    }

    static uint8_t fromFloat(const float &value) {
        return static_cast<int>(std::clamp(value, 0.f, 1.f) * 255.f);
    }

    static constexpr std::string_view name = "uint8";
    static constexpr FilmPixelDepth pixelDepth = FilmPixelDepth::UINT8;
};

}