#pragma once

#include "PixelFormat.h"
#include "basics/Bound2d.h"
#include "basics/Resolution.h"
#include "scene/RegionToRender.h"
#include "utils/DtoUtils.h"
#include <fmt/ranges.h>
#include <fmt/std.h>
#include <vector>

namespace crayg {

CRAYG_DTO_3(ChannelSpec, std::string, name, PixelFormat, pixelFormat, int, colorChannelCount);

CRAYG_DTO_3(ImageSpec, Resolution, resolution, std::vector<ChannelSpec>, channels, std::optional<Bounds2di>,
            regionToRender);

class ImageSpecBuilder {
  public:
    ImageSpecBuilder(const Resolution &resolution) {
        imageSpec = ImageSpec(resolution, {{"rgb", PixelFormat::FLOAT, 3}}, std::nullopt);
    }

    ImageSpecBuilder &addAlphaChannel() {
        createGreyFloatChannel("alpha");
        return *this;
    }

    ImageSpecBuilder &addDepthChannel() {
        createGreyFloatChannel("depth");
        return *this;
    }

    ImageSpecBuilder &createRgbFloatChannel(const std::string &name) {
        imageSpec.channels.emplace_back(name, PixelFormat::FLOAT, 3);
        return *this;
    }

    ImageSpecBuilder &createGreyFloatChannel(const std::string &name) {
        imageSpec.channels.emplace_back(name, PixelFormat::FLOAT, 1);
        return *this;
    }

    ImageSpecBuilder &createRgbUInt8Channel(const std::string &name) {
        imageSpec.channels.emplace_back(name, PixelFormat::UINT8, 3);
        return *this;
    }

    ImageSpecBuilder &createGreyUInt8Channel(const std::string &name) {
        imageSpec.channels.emplace_back(name, PixelFormat::UINT8, 1);
        return *this;
    }

    ImageSpecBuilder &createVector3fChannel(const std::string &name) {
        imageSpec.channels.emplace_back(name, PixelFormat::FLOAT, 3);
        return *this;
    }

    ImageSpecBuilder &addRenderRegion(const RegionToRender &regionToRender) {
        imageSpec.regionToRender = regionToRender.toPixelRegion(imageSpec.resolution);
        return *this;
    }

    ImageSpec finish() {
        return imageSpec;
    }

  private:
    ImageSpec imageSpec;
};

} // crayg
