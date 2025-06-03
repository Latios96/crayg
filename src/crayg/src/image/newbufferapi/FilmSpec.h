#pragma once

#include "basics/Bound2d.h"
#include "basics/Resolution.h"
#include "film/buffers/FilmBufferType.h"
#include "film/buffers/FilmPixelDepth.h"
#include "scene/RegionToRender.h"
#include "utils/DtoUtils.h"
#include <fmt/ranges.h>
#include <fmt/std.h>
#include <ostream>
#include <vector>

namespace crayg {

struct FilmBufferSpec {

    FilmBufferSpec(const std::string &name, FilmBufferType bufferType, FilmPixelDepth pixelDepth, int channelCount);

    std::string name;
    FilmBufferType bufferType;
    FilmPixelDepth pixelDepth;
    int channelCount;

    bool operator==(const FilmBufferSpec &rhs) const;
    bool operator!=(const FilmBufferSpec &rhs) const;
    friend std::ostream &operator<<(std::ostream &os, const FilmBufferSpec &spec);
};

CRAYG_DTO_3(FilmSpec, Resolution, resolution, std::vector<FilmBufferSpec>, channels, std::optional<Bounds2di>,
            regionToRender);

class FilmSpecBuilder {
  public:
    FilmSpecBuilder(const Resolution &resolution);

    FilmSpecBuilder &addChannel(const FilmBufferSpec &spec);
    FilmSpecBuilder &addRenderRegion(const RegionToRender &regionToRender);
    FilmSpec finish();

  private:
    FilmSpec filmSpec;
};

}

template <> struct fmt::formatter<crayg::FilmBufferSpec> : ostream_formatter {};
