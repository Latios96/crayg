#pragma once

#include "basics/Bound2d.h"
#include "basics/Resolution.h"
#include <fmt/ostream.h>
#include <ostream>
#include <variant>

namespace crayg {

typedef Bounds2di PixelRegion;
typedef Bounds2df NDCRegion;

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

template <> struct fmt::formatter<std::optional<crayg::RegionToRender>> {
    template <typename ParseContext> constexpr auto parse(ParseContext &ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(std::optional<crayg::RegionToRender> const &bounds, FormatContext &ctx) {
        return fmt::format_to(ctx.out(), "{}", bounds.has_value() ? fmt::format("{}", *bounds) : "<empty>");
    };
};