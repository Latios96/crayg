#pragma once

#include "basics/Bound2d.h"
#include "basics/Resolution.h"
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
    // ostream
    // formatter

    PixelRegion toPixelRegion(const Resolution &resolution) const;
    NDCRegion toNDCRegion(const Resolution &resolution) const;

    bool isPixelRegion() const;

    bool isNDCRegion() const;

    friend std::ostream &operator<<(std::ostream &os, const RegionToRender &render);

    std::variant<PixelRegion, NDCRegion> region;
};

}