#pragma once

#include "compatibility/openexr/fmt/ImfCompression_formatter.h"
#include "compatibility/openexr/fmt/ImfPixelType_formatter.h"
#include "crayg/foundation/areaiterators/tiles/TileSequenceType.h"
#include "image/io/imageformatwriters/exr/OpenExrFormatWriteOptions.h"
#include "integrators/IntegratorType.h"
#include "intersectors/IntersectorType.h"
#include "renderer/tilesamplers/TileSamplerType.h"
#include "scene/camera/CameraType.h"
#include "scene/shadingnetworks/shadingnodes/ColorToFloat.h"
#include "scene/shadingnetworks/shadingnodes/PrimVarReaders.h"
#include <ImfCompression.h>
#include <ImfPixelType.h>
#include <fmt/format.h>
#include <pxr/usd/sdf/types.h>
#include <pxr/usd/sdf/valueTypeName.h>
#include <string>

namespace crayg {

template <typename CraygType> struct UsdTypeUtil {};

template <> struct UsdTypeUtil<int> {
    inline static pxr::SdfValueTypeName sdfValueTypeName = pxr::SdfValueTypeNames->Int;

    static int convert(const int i) {
        return i;
    }
};

template <> struct UsdTypeUtil<float> {
    inline static pxr::SdfValueTypeName sdfValueTypeName = pxr::SdfValueTypeNames->Float;

    static float convert(const float f) {
        return f;
    }
};

template <> struct UsdTypeUtil<std::string> {
    inline static pxr::SdfValueTypeName sdfValueTypeName = pxr::SdfValueTypeNames->String;

    static std::string &convert(std::string &str) {
        return str;
    }
};

template <> struct UsdTypeUtil<CameraType> {
    inline static pxr::SdfValueTypeName sdfValueTypeName = pxr::SdfValueTypeNames->Token;

    static pxr::TfToken convert(CameraType cameraType) {
        return pxr::TfToken(fmt::format("{}", cameraType));
    }
};

template <> struct UsdTypeUtil<IntegratorType> {
    inline static pxr::SdfValueTypeName sdfValueTypeName = pxr::SdfValueTypeNames->Token;

    static pxr::TfToken convert(IntegratorType integratorType) {
        return pxr::TfToken(fmt::format("{}", integratorType));
    }
};

template <> struct UsdTypeUtil<IntersectorType> {
    inline static pxr::SdfValueTypeName sdfValueTypeName = pxr::SdfValueTypeNames->Token;

    static pxr::TfToken convert(IntersectorType intersectorType) {
        return pxr::TfToken(fmt::format("{}", intersectorType));
    }
};

template <> struct UsdTypeUtil<TileSequenceType> {
    inline static pxr::SdfValueTypeName sdfValueTypeName = pxr::SdfValueTypeNames->Token;

    static pxr::TfToken convert(TileSequenceType tileSequenceType) {
        return pxr::TfToken(fmt::format("{}", tileSequenceType));
    }
};

template <> struct UsdTypeUtil<TileSamplerType> {
    inline static pxr::SdfValueTypeName sdfValueTypeName = pxr::SdfValueTypeNames->Token;

    static pxr::TfToken convert(TileSamplerType tileSamplerType) {
        return pxr::TfToken(fmt::format("{}", tileSamplerType));
    }
};

template <> struct UsdTypeUtil<PrimVarReaderType> {
    inline static pxr::SdfValueTypeName sdfValueTypeName = pxr::SdfValueTypeNames->Token;

    static pxr::TfToken convert(PrimVarReaderType primVarReaderType) {
        return pxr::TfToken(fmt::format("{}", primVarReaderType));
    }
};

template <> struct UsdTypeUtil<ColorToFloatMode> {
    inline static pxr::SdfValueTypeName sdfValueTypeName = pxr::SdfValueTypeNames->Token;

    static pxr::TfToken convert(ColorToFloatMode colorToFloatMode) {
        return pxr::TfToken(fmt::format("{}", colorToFloatMode));
    }
};

template <> struct UsdTypeUtil<Imf::Compression> {
    inline static pxr::SdfValueTypeName sdfValueTypeName = pxr::SdfValueTypeNames->Token;

    static pxr::TfToken convert(Imf::Compression compression) {
        return pxr::TfToken(fmt::format("{}", compression));
    }
};

template <> struct UsdTypeUtil<Imf::PixelType> {
    inline static pxr::SdfValueTypeName sdfValueTypeName = pxr::SdfValueTypeNames->Token;

    static pxr::TfToken convert(Imf::PixelType pixelType) {
        return pxr::TfToken(fmt::format("{}", pixelType));
    }
};

template <> struct UsdTypeUtil<OpenExrDataWindow> {
    inline static pxr::SdfValueTypeName sdfValueTypeName = pxr::SdfValueTypeNames->Token;

    static pxr::TfToken convert(OpenExrDataWindow openExrDataWindow) {
        return pxr::TfToken(fmt::format("{}", openExrDataWindow));
    }
};

}
