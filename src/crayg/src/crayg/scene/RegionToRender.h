#pragma once

#include "crayg/foundation/math/geometry/Bound2d.h"
#include "crayg/foundation/math/geometry/Resolution.h"
#include <fmt/ostream.h>
#include <ostream>
#include <variant>

namespace crayg {

typedef Bounds2di PixelRegion;
typedef Bounds2df NDCRegion;

// NDC is as specified in https://openusd.org/dev/api/usd_render_page_front.html#UsdRenderCroppingTilingOverscan

class RegionToRender {
  public:
    RegionToRender() = default;
    explicit RegionToRender(const PixelRegion &pixelRegion);
    explicit RegionToRender(const NDCRegion &ndcRegion);

    static RegionToRender fromString(const std::string &str);
    std::string toString() const;

    PixelRegion toPixelRegion(const Resolution &resolution) const;
    NDCRegion toNDCRegion(const Resolution &resolution) const;

    bool isPixelRegion() const;
    bool isNDCRegion() const;

    friend std::ostream &operator<<(std::ostream &os, const RegionToRender &render);
    bool operator==(const RegionToRender &rhs) const;
    bool operator!=(const RegionToRender &rhs) const;

    std::variant<PixelRegion, NDCRegion> region;
};

}

template <> struct fmt::formatter<crayg::RegionToRender> : ostream_formatter {};
