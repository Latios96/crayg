#pragma once

#include "buffers/FilmBufferType.h"
#include "crayg/foundation/math/geometry/Bound2d.h"
#include "crayg/foundation/math/geometry/Bound2d_formatter.h"
#include "crayg/foundation/math/geometry/Resolution.h"
#include "crayg/foundation/math/geometry/Resolution_formatter.h"
#include "crayg/foundation/objects/DtoUtils.h"
#include "image/PixelFormat.h"
#include "scene/RegionToRender.h"
#include <fmt/ranges.h>
#include <fmt/std.h>
#include <ostream>
#include <vector>

namespace crayg {

struct FilmBufferSpec {

    FilmBufferSpec(const std::string &name, FilmBufferType bufferType, PixelFormat pixelFormat, int channelCount);

    std::string name;
    FilmBufferType bufferType;
    PixelFormat pixelFormat;
    int channelCount;

    bool operator==(const FilmBufferSpec &rhs) const;
    bool operator!=(const FilmBufferSpec &rhs) const;
    friend std::ostream &operator<<(std::ostream &os, const FilmBufferSpec &spec);
};
}

template <> struct fmt::formatter<crayg::FilmBufferSpec> : ostream_formatter {};

namespace crayg {

CRAYG_DTO_3(FilmSpec, Resolution, resolution, std::vector<FilmBufferSpec>, channels, std::optional<Bounds2di>,
            regionToRender);

class FilmSpecBuilder {
  public:
    FilmSpecBuilder(const Resolution &resolution);
    FilmSpecBuilder(const Resolution &resolution, FilmBufferType colorChannelBufferType,
                    PixelFormat colorChannelPixelFormat);

    FilmSpecBuilder &addChannel(const FilmBufferSpec &spec);
    FilmSpecBuilder &addRenderRegion(const RegionToRender &regionToRender);
    FilmSpec finish();

  private:
    FilmSpec filmSpec;
};

}
